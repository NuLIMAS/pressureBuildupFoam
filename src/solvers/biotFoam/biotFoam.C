/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2010 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    biotFoam is a modified version of solidDisplacementFoam

Description
    Transient segregated finite-volume solver of the Biot consolidation equations
    for linear-elastic, small-strain deformation of a solid skeleton coupled with
    pore water flow and pressure governed by Darcy's law.

    Simple linear elasticity structural analysis code.
    Solves for the displacement vector field D and the pore water pressure p.
    Also generating the stress tensor field sigma.
    
Author
    Johan Roenby, DHI Water & Environment

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "constitutiveModel.H"
#include "solidInterface.H"
#include "multiMaterial.H"
#include "poroElastic.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

Foam::tmp<scalarField> indicator
(
    const fvMesh& mesh,
    const label i
)
{
    const scalarField& mat = mesh.lookupObject<volScalarField>("materials");

    tmp<scalarField> tresult(new scalarField(mat.size(), 0.0));
    scalarField& result = tresult();

    forAll (mat, matI)
    {
        if (mat[matI] > i - SMALL && mat[matI] < i + 1 - SMALL)
        {
            result[matI] = 1.0;
        }
    }

    return tresult;
}


int main(int argc, char *argv[])
{
    #include "setRootCase.H"

    #include "createTime.H"
    #include "createMesh.H"
    #include "readMaterialProperties.H"
    #include "readPoroElasticControls.H"
    #include "createFields.H"
    #include "readDivSigmaExpMethod.H"
    #include "createSolidInterfaceNoModify.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nCalculating displacement field\n" << endl;

    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        #include "readPoroElasticControls.H"

        label iCorr = 0;
        scalar pResidual = 1.0e10;
        scalar DResidual = 1.0e10;
        scalar residual = 1.0e10;

        do
        {
                       D.storePrevIter();
                       p.storePrevIter();

                       fvScalarMatrix pEqn
			(
				fvm::ddt(Dp1,p)       == fvm::laplacian(Dp2, p) - fvc::div(fvc::ddt(Dp3,D))
			);
                       pEqn.relax();
                       pResidual=pEqn.solve().initialResidual();
                       p.relax();

                       fvVectorMatrix DEqn
			(
			        fvm::laplacian(2*mu + lambda, D, "laplacian(DD,D)") + divSigmaExp   == fvc::grad(p)
			);

                       if (solidInterfaceCorr)
                       {
                           solidInterfacePtr->correct(DEqn);
                       }

			DResidual=DEqn.solve().initialResidual();
                       D.relax();

			gradD = fvc::grad(D);
			sigmaD = mu*twoSymm(gradD) + (lambda*I)*tr(gradD);
			divSigmaExp = fvc::div(sigmaD - (2*mu + lambda)*gradD,"div(sigmaD)");

                       residual = max(pResidual,DResidual);

        } while
        (
            (residual > convergenceTolerance && ++iCorr < nCorr)
        );

        Info << "number of iterations " << iCorr << endl;

        //if (predictor)
        //{
        //    V = fvc::ddt(U);
        //    gradV = fvc::ddt(gradU);
        //    snGradV = (snGradU - snGradU.oldTime())/runTime.deltaT();
        //}

        #include "calculateStress.H"

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //

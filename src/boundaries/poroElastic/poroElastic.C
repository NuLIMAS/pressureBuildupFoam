/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     4.1
    \\  /    A nd           | Web:         http://www.foam-extend.org
     \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "poroElastic.H"
#include "addToRunTimeSelectionTable.H"
#include "zeroGradientFvPatchFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(poroElastic, 0);
    addToRunTimeSelectionTable(rheologyLaw, poroElastic, dictionary);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from dictionary
Foam::poroElastic::poroElastic
(
    const word& name,
    const volSymmTensorField& sigma,
    const dictionary& dict
)
:
    linearElastic(name, sigma, dict),
    n_(dict.lookup("n")),
    k_(dict.lookup("k"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::poroElastic::~poroElastic()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //



Foam::tmp<Foam::volScalarField> Foam::poroElastic::n() const
{
    return tmp<volScalarField>
    (
        new volScalarField
        (
            IOobject
            (
                "n",
                mesh().time().timeName(),
                mesh(),
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh(),
            n_,
            zeroGradientFvPatchScalarField::typeName
        )
    );
}

Foam::tmp<Foam::volScalarField> Foam::poroElastic::k() const
{
    return tmp<volScalarField>
    (
        new volScalarField
        (
            IOobject
            (
                "k",
                mesh().time().timeName(),
                mesh(),
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh(),
            k_,
            zeroGradientFvPatchScalarField::typeName
        )
    );
}


// ************************************************************************* //

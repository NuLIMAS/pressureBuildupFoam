Info<< "Reading wave properties\n" << endl;
IOdictionary waveProperties
(
    IOobject
    (
        "waveProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);

Info<< "Reading material properties\n" << endl;

IOdictionary materialProperties
(
    IOobject
    (
        "materialProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);



dimensionedScalar relDensity(materialProperties.lookup("relDensity"));
dimensionedScalar T("T",dimensionSet(0, 0, 1, 0, 0), waveProperties.lookup("period") );
dimensionedScalar gammaD(materialProperties.lookup("gammaD"));


Info<< "Initializing field k0\n" << endl;
volScalarField k0
(
    IOobject
    (
        "k0",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(materialProperties.lookup("k0")),
    zeroGradientFvPatchScalarField::typeName
);

Info<< "Initializing field alpha\n" << endl;
volScalarField alpha
(
    IOobject
    (
        "alpha",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(materialProperties.lookup("alpha")),
    zeroGradientFvPatchScalarField::typeName
);

volScalarField beta
(
    IOobject
    (
        "beta",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(materialProperties.lookup("beta")),
    zeroGradientFvPatchScalarField::typeName
);





const cellZone& cz1 = mesh.cellZones()["solidZones"];
    forAll(cz1, czi)
    {

        alpha[cz1[czi]]  = 0.764;
        beta[cz1[czi]]   = 0.28;
        k0[cz1[czi]]     = 0.38434;
 
    }




alpha.correctBoundaryConditions();
beta.correctBoundaryConditions();
k0.correctBoundaryConditions();



volScalarField sigma0
(
    IOobject
    (
        "sigma0",
        runTime.timeName(),
        mesh, 
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    gammaD*(max(mesh.C().component(vector::Z)) -    mesh.C().component(vector::Z))*((1.0+(2.0*k0))/3.0)
);


volScalarField tauAmp = sqrt(2.0* tauRMS);

liqueCriteria.internalField() = pE.internalField()/sigma0.internalField();
liqueCriteria.correctBoundaryConditions();


volScalarField numCyc 
(
    IOobject
    (
        "numCyc",
        runTime.timeName(),
        mesh, 
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("zero", dimless, 0.0),
    zeroGradientFvPatchScalarField::typeName
);


numCyc.internalField() =
    Foam::pow
    (
        (1.0/alpha)
       *mag(tauAmp.internalField()/sigma0.internalField()) + SMALL, (1.0/beta)
    );
   
numCyc.correctBoundaryConditions();
      
  
   
 Info<< "Calculate source term\n" << endl;   
        
volScalarField f
(
    IOobject
    (
        "f",
        runTime.timeName(),
        mesh, 
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    sigma0/(numCyc * T),
    zeroGradientFvPatchScalarField::typeName
);
    
f.correctBoundaryConditions();

    forAll(cz1, czi)
    {
        f[cz1[czi]]  =0;
    }





//volScalarField cv("cv", (mu * k / gamma) * ((2-2*nu)/ ((1-2*nu)+(2-2*nu)*(n*mu/Kprime))));




runTime.write();     
        

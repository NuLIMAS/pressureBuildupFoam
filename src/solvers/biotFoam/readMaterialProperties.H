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

/*
Info<< "Initializing field nu\n" << endl;
volScalarField nu
(
    IOobject
    (
        "nu",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(materialProperties.lookup("nu")),
    zeroGradientFvPatchScalarField::typeName
);*/


Info<< "Initializing field k\n" << endl;
volScalarField k
(
    IOobject
    (
        "k",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("zero", dimLength/dimTime,0.0),
    zeroGradientFvPatchScalarField::typeName
);


Info<< "Initializing field n\n" << endl;
volScalarField n
(
    IOobject
    (
        "n",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("zero",dimless,0.0),
    zeroGradientFvPatchScalarField::typeName
);









Info<< "Initializing field K\n" << endl;
volScalarField K
(
    IOobject
    (
        "K",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar(materialProperties.lookup("K")),
    zeroGradientFvPatchScalarField::typeName
);






Info<< "Initializing field Sr\n" << endl;
volScalarField Sr
(
    IOobject
    (
        "Sr",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar(materialProperties.lookup("Sr")),
    zeroGradientFvPatchScalarField::typeName
);



Sr.correctBoundaryConditions();



dimensionedScalar p0(materialProperties.lookup("p0"));
dimensionedScalar gamma(materialProperties.lookup("gamma"));











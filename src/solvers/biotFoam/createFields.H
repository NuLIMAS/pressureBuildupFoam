Info<< "Reading field D\n" << endl;
volVectorField D
(
    IOobject
    (
        "D",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

    volTensorField gradD
    (
        IOobject
        (
            "grad(D)",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedTensor("zero", dimless, tensor::zero)
    );

    surfaceVectorField snGradD
    (
        IOobject
        (
            "snGrad(D)",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedVector("zero", dimless, vector::zero)
    );

Info<< "Reading pore pressure field p\n" << endl;

volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Calculating stress field sigmaD\n" << endl;
volSymmTensorField sigmaD
(
    IOobject
    (
        "sigmaD",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedSymmTensor("zero", dimForce/dimArea, symmTensor::zero)

);

constitutiveModel rheology(sigmaD, D);
volScalarField mu = rheology.mu();
volScalarField lambda = rheology.lambda();
surfaceScalarField muf = rheology.muf();
surfaceScalarField lambdaf = rheology.lambdaf();

     

const multiMaterial& mat = dynamic_cast<const multiMaterial&>(rheology.law());

const PtrList<rheologyLaw>& laws = mat;

n.internalField() = 0.0;
k.internalField() = 0.0;

forAll (laws, lawI)
{
    const poroElastic& poroElasticLaw =
        dynamic_cast<const poroElastic&>(laws[lawI]);
    n.internalField() +=
        indicator(mesh, lawI)*poroElasticLaw.n();
    k.internalField() +=
        indicator(mesh, lawI)*poroElasticLaw.k();
}

n.correctBoundaryConditions();
k.correctBoundaryConditions();

Info<< "Calculating explicit part of div(sigma) divSigmaExp\n" << endl;
volVectorField divSigmaExp
(
    IOobject
    (
        "divSigmaExp",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    fvc::div(sigmaD)
);

Info<< "Initializing tauXZ field\n" << endl;
volScalarField tauXZ
(
    IOobject
    (
        "tauXZ",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    sigmaD.component(symmTensor::XZ)
);
q
Info<< "Initializing nu field\n" << endl;
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
    lambda/(2*(lambda+mu))
);




volScalarField Kprime = 1.0/(1.0/K + (1.0-Sr)/p0);
volScalarField Kdash = 1.0/Kprime;


Info<< "Initializing cv field\n" << endl;
volScalarField cv
(
    IOobject
    (
        "cv",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    (mu * k / gamma) * ((2-2*nu)/ ((1-2*nu)+(2-2*nu)*(n*mu/Kprime)))
);






Info<< "Initializing field Dp1\n" << endl;
volScalarField Dp1
(
    IOobject
    (
        "Dp1",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    (n*Kdash)
);


Info<< "Initializing field Dp2\n" << endl;
volScalarField Dp2
(
    IOobject
    (
        "Dp2",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    (k/gamma)
);



Info<< "Initializing field Dp3\n" << endl;
volScalarField Dp3
(
    IOobject
    (
        "Dp3",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    (Kprime*Kdash)
);



if (compactNormalStress)
{
    divSigmaExp -= fvc::laplacian(2*mu + lambda, D, "laplacian(DD,D)");
}
else
{
    divSigmaExp -= fvc::div((2*mu + lambda)*fvc::grad(D), "div(sigmaD)");
}

/*constitutiveModel rheology(sigmaD, D);

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
*/


Info<< "Reading period averaged excess pore pressure  field pE\n" << endl;

volScalarField pE
(
    IOobject
    (
        "pE",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


volScalarField liqueCriteria
(
    IOobject
    (
        "liqueCriteria",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("zero", dimless, 0.0),
    zeroGradientFvPatchScalarField::typeName
);




volScalarField tauRMS
(
    IOobject
    (
        "tauXZPrime2Mean",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
    mesh   
);
volScalarField cv
(
    IOobject
    (
        "cv",
        runTime.timeName(),
        mesh, 
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
    mesh

);





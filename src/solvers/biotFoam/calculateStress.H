if (runTime.outputTime())
{

    volSymmTensorField sigma
    (
        IOobject
        (
            "sigma",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        sigmaU - I*p
    );

    volScalarField sigmaEq
    (
        IOobject
        (
            "sigmaEq",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        sqrt((3.0/2.0)*magSqr(dev(sigma)))
    );

    Info<< "Max sigmaEq = " << max(sigmaEq).value()
        << endl;

    volVectorField V
    (
        IOobject
        (
            "V",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        -(k/gamma)*fvc::grad(p)
    );
    
tauXZ = sigmaU.component(symmTensor::XZ);
    
runTime.write();  

}
    


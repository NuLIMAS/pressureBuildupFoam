cd SumerExample_b
system('./Allclean')
system('./Allrun')
system ('cp -r 13.7/cv ../SumerBookExample4_p/0/')
system ('cp -r 13.7/tauXZPrime2Mean ../SumerBookExample4_p/0/')
cd ../SumerExample_p
system('./Allclean')
system('./Allrun')
comparison

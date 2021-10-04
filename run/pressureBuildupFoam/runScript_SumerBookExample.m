cd SumerBookExample4_b
system('./Allclean')
system('./Allrun')
system ('cp -r 900/cv ../SumerBookExample4_p/0/')
system ('cp -r 900/tauXZPrime2Mean ../SumerBookExample4_p/0/')
cd ../SumerBookExample4_p
system('./Allclean')
system('./Allrun')
comaparison

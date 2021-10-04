import gmsh
import sys
import math

def surfaceFromPoints(gmsh, pts, closed= True):
    factory = gmsh.model.geo
    if closed:
    	l = [factory.addLine(pts[-1], pts[0])]
    else:
        l = []
    l = l + [factory.addLine(pts[i], pts[i + 1]) for i in range(0, len(pts) - 1)]
    if closed:
    	return factory.addPlaneSurface([factory.addCurveLoop(l)])
    else:
      	return factory.addPlaneSurface([factory.addWire(l)])

gmsh.initialize()
model = gmsh.model
factory = model.geo
model.add('test')

gmsh.option.setNumber("Mesh.Algorithm", 8)

gmsh.option.setNumber('General.Terminal', 1)


pts = []

# Define points
x1=0
y1=0
z1=0

dx1=0.3
dz1=0.17
dz2=0.015





dy1=40
dy4=1000
y2=y1+dy4
dy5=150
delta=0.004
delta2=0.0005

pts.append(factory.addPoint(x1, y1, z1-dz1, delta))
pts.append(factory.addPoint(x1+3*dx1, y1, z1-dz1, delta))
pts.append(factory.addPoint(x1+3*dx1, y1, z1, delta))
pts.append(factory.addPoint(x1+2*dx1, y1, z1, delta2))
pts.append(factory.addPoint(x1+2*dx1, y1, z1-dz2, delta2))
pts.append(factory.addPoint(x1+dx1, y1, z1-dz2, delta2))
pts.append(factory.addPoint(x1+dx1, y1, z1, delta2))
pts.append(factory.addPoint(x1, y1, z1, delta))










s = surfaceFromPoints(gmsh, pts)

ov = gmsh.model.geo.extrude([(2, s)], 0, 0.02, 0, [1], recombine=True)


print(ov)

gmsh.model.geo.synchronize()

gmsh.model.mesh.setRecombine(2, s)
gmsh.option.setNumber("Mesh.Algorithm", 8)


ps3 = model.addPhysicalGroup(2, [21])
model.setPhysicalName(2, ps3, "left")
ps4 = model.addPhysicalGroup(2, [29])
model.setPhysicalName(2, ps4, "right")
ps5 = model.addPhysicalGroup(2, [49,33])
model.setPhysicalName(2, ps5, "seaBed")	
ps6 = model.addPhysicalGroup(2, [41,45,37])
model.setPhysicalName(2, ps6, "rocker")
ps7 = model.addPhysicalGroup(2, [1,50])
model.setPhysicalName(2, ps7, "frontBack")
ps8 = model.addPhysicalGroup(2, [25])
model.setPhysicalName(2, ps8, "soilDomainBottom")
vs = gmsh.model.addPhysicalGroup(3, [1])
gmsh.model.setPhysicalName(1, vs, "Volume")

gmsh.model.mesh.generate(2)
gmsh.write("seabed.vtk")
# Note that you could also apply the recombination algorithm and/or the
# subdivision step explicitly after meshing, as follows:
#
# gmsh.model.mesh.generate(2)
# gmsh.model.mesh.recombine()
# gmsh.option.setNumber("Mesh.SubdivisionAlgorithm", 1)
# gmsh.model.mesh.refine()


gmsh.model.mesh.generate(3)



'''ps = gmsh.model.addPhysicalGroup(3, [1])
gmsh.model.setPhysicalName(1, ps, "Volume")'''
gmsh.write("seabed.msh")



# Launch the GUI to see the results:
if '-nopopup' not in sys.argv:
    gmsh.fltk.run()

gmsh.finalize()

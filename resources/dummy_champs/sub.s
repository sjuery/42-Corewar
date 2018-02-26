.name "sub champ"
.comment "subtract two registries and put result in a registry"


	ld %14,r02
	ld %0,r01
	ld 42,r03
	sub r1,r2,r3
	sub r3,r2,r1
	sub r1,r3,r3

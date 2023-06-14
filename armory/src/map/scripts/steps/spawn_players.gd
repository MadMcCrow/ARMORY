# SpawnPlayers
#	Find Player Starts for the game

# default values :
@export PlayerCount : int

# the main function of all map-script
func run (grid : MapGrid, params : Dictionary) :
	var radius = params.get()
	var points = PoissonDiscSampling.sample_region_shape()

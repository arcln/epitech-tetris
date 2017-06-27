Usage: ./tetris [options]
Options:
	--help			Display this help
	-l --level={num}	Start Tetris at level num (def: 1)
	-kl --key-left={K}	Move the tetrimino LEFT using the K key (def: left arrow)
	-kr --key-right={K}	Move the tetrimino RIGHT using the K key (def: right arrow)
	-kt --key-turn={K}	TURN the tetrimino clockwise 90d using the K key (def: up arrow)
	-kd --key-drop={K}	DROP the tetrimino using the K key (def: down arrow)
	-kq --key-quit={K}	QUIT the game using the K key (def: 'Q' key)
	-kp --key-pause={K}	PAUSE/RESTART the game using the K key (def: space bar)
	--map-size={row,col}	Set the number of rows and columns of the map (def: 20,10)
	-w --without-next	Hide next tetrimino (def: false)
	-d --debug		Debug mode (def: false)

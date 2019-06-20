<html>
	<head>
		<title> Panel du Mélangeur MVAS </title>
        <link href="./../css/comtest.css" rel="stylesheet" type="text/css">
        <link rel="stylesheet" href="https://unpkg.com/purecss@1.0.0/build/pure-min.css" integrity="sha384-nn4HPE8lTHyVtfCBi5yW9d20FjT8BJwUXyWZT9InLYax14RDjBj46LmSztkmNP9w" crossorigin="anonymous">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.2.4/jquery.min.js"></script>
	</head>
	<body>
    
    <?php 
        $file = "./../cache/buttonvalue.txt";
        $content = file_get_contents($file);
        $button_value = explode(" ", $content);
    ?>

    <h1> COM WEB TEST </h1>
		<div id="principale">
			<div id="panel">
				<div id="audio">
                    <h3>Son </h3>
                    Input 1 
					<div class="bar"><input type="range" class="slider" min="0 " max="1024" value="<?php print($button_value[0]); ?>"></div>
                    Input 2
                    <div class="bar"><input type="range" class="slider" min="0" max="1024" value="<?php print($button_value[1]); ?>"></div>
                    Input 3
                    <div class="bar"><input type="range" class="slider" min="0" max="1024" value="<?php print($button_value[2]); ?>"></div>
                    Input 4
					<div class="bar"><input type="range" class="slider" min="0" max="1024" value="<?php print($button_value[3]); ?>"></div>
                    Auxiliary
					<div class="bar"><input type="range" class="slider" min="0" max="1024" value="<?php print($button_value[4]); ?>"></div>
                    Output left
                    <div class="bar"><input type="range" class="slider" min="0" max="1024" value="<?php print($button_value[5]); ?>"></div>
                    Output right
					<div class="bar"><input type="range" class="slider" min="0" max="1024" value="<?php print($button_value[6]); ?>"></div>

					<div id="video">
                        <?php
                            print("<h3> Program </h3>");
                            if ($button_value[7] == 1)
                            {
                                print('<button class="pure-button pure-button-active">PGM1</button>');
                            }
                            else
                            {
                                print('<button class="pure-button" disabled>PGM1</button>');
                            }

                            if ($button_value[8] == 1)
                            {
                                print('<button class="pure-button pure-button-active">PGM2</button>');
                            }
                            else
                            {
                                print('<button class="pure-button" disabled>PGM2</button>');
                            }

                            if ($button_value[9] == 1)
                            {
                                print('<button class="pure-button pure-button-active">PGM3</button>');
                            }
                            else
                            {
                                print('<button class="pure-button" disabled>PGM3</button>');
                            }

                            if ($button_value[10] == 1)
                            {
                                print('<button class="pure-button pure-button-active">PGM4</button>');
                            }
                            else
                            {
                                print('<button class="pure-button" disabled>PGM4</button>');
                            }
                            
                            print("<h3> Preview </h3>");
                            if ($button_value[11] == 1)
                            {
                                print('<button class="pure-button pure-button-active">PVW1</button>');
                            }
                            else
                            {
                                print('<button class="pure-button" disabled>PVW1</button>');
                            }

                            if ($button_value[12] == 1)
                            {
                                print('<button class="pure-button pure-button-active">PVW2</button>');
                            }
                            else
                            {
                                print('<button class="pure-button" disabled>PVW2</button>');
                            }

                            if ($button_value[13] == 1)
                            {
                                print('<button class="pure-button pure-button-active">PVW3</button>');
                            }
                            else
                            {
                                print('<button class="pure-button" disabled>PVW3</button>');
                            }

                            if ($button_value[14] == 1)
                            {
                                print('<button class="pure-button pure-button-active">PVW4</button>');
                            }
                            else
                            {
                                print('<button class="pure-button" disabled>PVW4</button>');
                            }
                            ?>
                            
						<div class="bar"><input type="range" class="slider" min="1" max="1024" value="<?php print($button_value[15]); ?>">
                        
                         </div>
						  
						
						
					</div>
				</div>
			</div>
			
		</div>
        <script>
        setInterval(load_value,200);
        function load_value() {
            $('#principale').load("./../background/load_panel.php")         
        }
        </script>
	</body>
	
</html>

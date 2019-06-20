<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Minimalist Video Audio Switcher - Error page</title>
        <link href="./../../../css/style.css" rel="stylesheet" type="text/css">
    </head>  
    <body>
    
        <div class="cadre">
            <center><h1>Minimalist Video Audio Switcher</h1>
            <h2>Infos DeckLink</h2>
		<?php 
		$config = shell_exec("aplay -c 1 -t raw -r 22050 -f mu_law final.wav ");
                echo($config); 
            	?>
            </div>

        <div class="logo">
            <a href="https://uphf.fr/"><img src="./../../../image/dream.png"></a>
        </div>
</div>
</body>
    <footer>
        <colorbluewhite>@MVAS TEAM 2019 | About</colorblue>
    </footer>

</html>

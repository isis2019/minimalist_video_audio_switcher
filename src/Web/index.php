<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Minimalist Video Audio Switcher - Welcome</title>
        <link href="./css/coming.css" rel="stylesheet" type="text/css">
        <link rel="stylesheet" href="https://unpkg.com/purecss@1.0.0/build/pure-min.css" integrity="sha384-nn4HPE8lTHyVtfCBi5yW9d20FjT8BJwUXyWZT9InLYax14RDjBj46LmSztkmNP9w" crossorigin="anonymous">
    </head>

    <body>
        <div class="background">
                <div id="particles-js"></div>
                                    <div class="toptext">
                <p></p>
            </div>
            <div class="middletext">
                <h1>Minimalist Video Audio Switcher</h1>
                <hr>
                <p>Video Switcher status:

                <?php $config = exec("ps auwx | grep \"mvas_qt_interface\" | grep -qv grep ; if [ $? -eq 0 ] ; then echo \"OK\" ; else echo \"No\" ; fi");
                echo $config; ?> </p>

                <?php
                    if ($config == "OK")
                    {
                        print("<a class='pure-button' href='./page/connexion.php'>Control Panel</a><br>");
                    }
                    else
                    
                    {
                        print("<a class='pure-button pure-button-disabled'>Control Panel</a><br>");
                    }
                ?>
            </div>
            <div class="bottext">
                <p>Coded with love, without cookies</p>
            </div>
        </div>
                
    </body>
</html>

<script src="./js/particles.js"></script>
<script> particlesJS.load('particles-js', './js/particles.json', function() {console.log('particles.json loaded...');})</script>

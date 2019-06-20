<?php
session_start();
if ($_SESSION['id'] == NULL and $_SESSION['password'] == NULL)
{
    header('Location: ./error.php');
}
?>

<!DOCTYPE html>
<html>
    <head>
        <title> Inscription | Photoshop Contest 2K19</title>
        <meta http-equiv="Content-type" content="text/html; charset=UTF-8"/> 
        <link href="./../../../css/style.css" rel="stylesheet" type="text/css">
        <link rel="stylesheet" href="https://unpkg.com/purecss@1.0.0/build/pure-min.css" integrity="sha384-nn4HPE8lTHyVtfCBi5yW9d20FjT8BJwUXyWZT9InLYax14RDjBj46LmSztkmNP9w" crossorigin="anonymous">
    </head>  
    <body>
    
        <div class="cadre">
            <center><h1>Minimalist Video Audio Switcher</h1>
            <h2>Bonjour, <?php echo($_SESSION['id']); ?> </h2>
            <a class='pure-button pure-button-primary' href='./info_decklink.php'>Video Card Caracteristics</a><br><br>
</center>
            </div>
        </div>

        <div class="logo">
            <a href="https://uphf.fr/"><img src="./../../../image/dream.png"></a>
        </div>
</div>
</body>
    <footer>
        <colorbluewhite>@MVAS TEAM 2019 | A Propos</colorblue>
    </footer>

</html>


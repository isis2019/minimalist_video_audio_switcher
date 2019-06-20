<?php

$id = $_POST['id'];
$password = $_POST['password'];

if  ($id == "DREAM2019" and $password == "jesuisundreameur")
{
    session_start();
    $_SESSION['id'] = $id;
    $_SESSION['password'] = $password;

    header('Location: ./../page/admin.php');
}

else
{
    header('Location: ./../page/error.php');
}
?>

<?php

if (isset($_POST['login']))
{
    include 'dbh.inc.php';

    $uid = mysqli_real_escape_string($conn, $_POST['uid']);
    $pwd = mysqli_real_escape_string($conn, $_POST['pwd']);

    //Error handlers

    //Check if inputs are empty
    if (empty($uid) || empty($pwd))
    {

    }

}
else {
    header("Location: ../index.php")
}

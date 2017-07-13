<?php

if (isset($_POST['submit']))
{
	include_once 'dbh.inc.php';

	$first = mysqli_real_escape_string($conn, $_POST['first']);
	$last = mysqli_real_escape_string($conn, $_POST['last']);
	$email = mysqli_real_escape_string($conn, $_POST['email']);
	$uid = mysqli_real_escape_string($conn, $_POST['uid']);
	$pwd = mysqli_real_escape_string($conn, $_POST['pwd']);

	// Error handlers

	//Check for empty fields
	if (empty($first) || empty($last) || empty($email) || empty($uid) || empty($pwd))
	{
		header("Location: ../index.php?index=empty");
		exit();
	}
	else
	{
		//Check if input characters are valid
		//
		//if (!preg_match("/^[a-zA-Z]*/$", $first))
		//{
		//	if (!preg_match("/^[a-zA-Z]*/$", $last))
		//	{
		//		header("Location: ../index.php?index=invalid");
		//		exit();
		//	}
		//}



				$sql = "SELECT * FROM users WHERE user_uid = '$uid'";
				$result = mysqli_query($conn, $sql);
				$resultCheck = mysqli_num_rows($result);

				if ($resultCheck > 0) {
					header("Location: ../index.php?index=usertaken");
					exit();
				} else {
					//Hash the password
					$hashedPwd = password_hash($pwd, PASSWORD_DEFAULT);

					//Insert the user into the database
					$sql = "INSERT INTO users (user_first, user_last, user_email, user_uid,
						 user_pwd) VALUES ('$first', '$last', '$email', '$uid', '$hashedPwd');";

					mysqli_query($conn, $sql);
					header("Location: ../index.php?index=success");
					exit();
				}

	}
}
else
{
	header("Location: ../index.php");
	exit();
}
?>

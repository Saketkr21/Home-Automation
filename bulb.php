<?php
	$s1 = $_GET['switch'];

	$a = mysqli_connect('185.27.134.10','root','','epiz_23718895_bulb');
	$ins="INSERT INTO A1 SET switch='$s1'";
	$a->query($ins);	
?>
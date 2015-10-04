<?php

	require_once("config/db.php");
	require_once("classes/Edit.php");
	$palabra = new Edit();
	$numero = $palabra->nextNumber();
	echo $numero;


	echo "<br>Se está subiendo el dato de temperatura con id " . $numero . "con el valor " . $_POST['value'];

	$crear = new Edit();
	$insert = $crear->putTables($numero, $_POST['value']);
	
	if($insert == true){
		echo "<br>se ha subido satisfactoriamente";
	}
	else{
		echo "la prueba ha ido mal";
	}
	

	

?>

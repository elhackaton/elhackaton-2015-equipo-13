<?php
class Edit{
	function nextNumber(){
   		$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASS, DB_NAME);
		if ($conn){
			$sql = "select id from temperature";
			$result = mysqli_query($conn,$sql);

			if (mysqli_num_rows($result) > 0) {
  		  
				// output data of each row
   				 while($row = mysqli_fetch_assoc($result)) {
		    			 $id = $row['id'];
		    			 $id++;
    				 }
			} 
			else {
    				$id = 1;
			}
			return $id;
		}
		else{
			header('Location: error.html');	//mensaje de error
		}
	}

	function putTables($id, $value){
		$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASS, DB_NAME);
		if ($conn){
			$sql2="insert into temperature(id, value) 
			values({$id}, {$value})";	//consulta sql a la base de datos para poner unos valores a una tabla determinada, los valores son del POST en index.php y el $sesion de inicio de

			$result2 = mysqli_query($conn,$sql2);
			if($result2){
				return true;
			}
			else{
				return false;
			}
			
		}
		else{
			header('Location: error.html');			//mensajes de error
		}
	}

	function showSomething ($whatToShow){

		$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASS, DB_NAME);
		
		if($conn){
			$sql3 = "select {$whatToShow} from temperature";
			$result = mysqli_query($conn, $sql3);
			$i = 0;
			if($result){
	
				while($row = mysqli_fetch_assoc($result)){
					$show[$i] = $row[$whatToShow];
					$i++;
				}
				return $show;
			}
			else{
				header('Location: error.html');
			}
		}
		else{
			header('Location: error.html');		
		}
	}

}
?>

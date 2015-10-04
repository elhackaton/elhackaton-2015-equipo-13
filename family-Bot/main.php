
<?php

function file_get_contents_utf8($fn) { 
     $content = file_get_contents($fn); 
      return mb_convert_encoding($content, 'UTF-8', 
          mb_detect_encoding($content, 'UTF-8, ISO-8859-1', true)); 
} 
$str = file_get_contents_utf8("http://www.meteosat.com/tiempo/almeria/tiempo-almeria.html");





$str2 = $str;
$str3 = $str;


	
		$str=(explode('<font size=4 color=#333333>', $str, 2));          //genera un $str['0'] y un $str['1']
	
	

	$str=(explode('</font>', $str['1'], 2));
	
	$dia = $str['0'];					//$str['0'] contiene lo cortado
	


$num = count($pic);
$num = $num -1;   //quitamos el error generado por el while

echo $dia;


	



	$str3=(explode('<td class="pluss">', $str3, 2));          //genera un $str['0'] y un $str['1']
	
	$str3=(explode('</td>', $str3['1'], 2));
	
	$temperatura = $str3['0'];					//$str['0'] contiene lo cortado
	


echo $temperatura;

$recomendacion = "";




if($temperatura < 20){

	echo "<br>Hoy hará frio, se recomienda que se lleve una chaqueta. ";
	$recomendacion = "hoy+hara+frio+se+recomienda+que+se+lleve+una+chaqueta";

}
else{
	if($temperatura >30){
		echo "<br>Hoy va a ser un día caluroso, se recomienda ir fresco. ";	
		$recomendacion = "hoy+es+un+dia+caluroso+ponte+a+la+sombra";
	}
	else{
		echo "<br>Hoy va a ser un día soleado. ";
		$recomendacion = "hoy+va+a+ser+un+dia+perfecto";
	}
}


echo "<iframe src=\"http://translate.google.com/translate_tts?ie=UTF-8&q=Hola+hoy+es+dia" . $dia . "y+va+a+hacer+una+temperatura+de+" . $temperatura . $recomendacion . "&tl=es\" height=\"1000\" width=\"1000\"><iframe>";




/*
for ($i = 0; $i < $num ; $i++){

	if($i == 0){$replaced = str_replace($pic[$i], $_GET['pic'], $str2);}
	else{$replaced = str_replace($pic[$i], $_GET['pic'], $replaced);}
	
}


echo $replaced;

*/





?>

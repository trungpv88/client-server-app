<?php
function IsPrime($number)
{
	if ($number <= 1) return 0;
	for ($i = 2; $i * $i <= $number; $i++)
	{
		if ($number % $i == 0) return 0;
	}
	return 1;
}

function PrintPrime($number)
{
//echo $_SERVER["argc"]."\n";
//echo $_SERVER["argv"][1]."\n";
	if($number < 2)
	{
		return -1;
	}
	else if($number == 2)
	{
		echo "$number\n";
	}
	else
	{
		echo "2".PHP_EOL;
		for ($i = 3; $i <= $number; $i = $i + 2)
		{
			if (IsPrime($i) == 1) 
				echo "$i".PHP_EOL;
		}
	}
}
PrintPrime($_SERVER["argv"][1])
?>

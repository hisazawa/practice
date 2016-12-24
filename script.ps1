$txt = ".\text.txt"
$prefix1 = "A:"
$prefix2 = "B:"
$ary = @(Get-Content $txt)
foreach($line in $ary){
    if($line.SubString(0,2) -eq $prefix1){
        $tmpline = $line.Replace("A:", "")
        $num1    = [int]$tmpline.Replace(" ","")
    }
    if($line.SubString(0,2) -eq $prefix2){
        $tmpline = $line.Replace("B:", "")
        $num2    = [int]$tmpline.Replace(" ","")
    }
}
[int]$num3 = 4
$num = $num1 + $num2 + $num3
"Answer:{0}" -F $num

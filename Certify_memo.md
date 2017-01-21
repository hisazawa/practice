Certify Memo
* **sscanf**  
**文字列workを数値year、monthに分割する。**  
～～～～～～～～～～～～～～～～～～～～～～～～～  
char work[128];  
int year;  
int month;  
sscanf(work, "%4d%2d", &year, &month);

* **sprintf**  
**数値year、monthを文字列workに書き込む**  
～～～～～～～～～～～～～～～～～～～～～～～～～  
sprintf(work, "%04d%02d", year - 5, month);

* **fopen**  
**ファイルをOPENする。(OPENしたときは後でCLOSEする)**  
～～～～～～～～～～～～～～～～～～～～～～～～～  
fp = fopen("keisoku.tbl", "rb");  
rb ：READのみ、バイナリファイル対応  
r+ ：READ/WRITE、テキストファイル対応  

* **strcmp**  
**文字列を比較する。(数値も比較できる)**  
～～～～～～～～～～～～～～～～～～～～～～～～～  
strcmp(sort_keisoku_tbl[i].nyuukai_date, work)) <= 0

* **fscanf**  
**ファイル(fp)の内容を構造体pに書き込む**  
～～～～～～～～～～～～～～～～～～～～～～～～～  
fscanf(fp, "%d", &p->kaiin_code);  
fscanf(fp, "%d", &p->count); ←fpは次の行に進んでいる  
fscanf(fp, "%s", p->max_date); ←数値と文字列の違いに注意!  
一行に空白区切りの文字列が複数ある場合  
fscanf(fp, "%lf %lf %lf %lf %lf",  
  &huka_sisuu[i][0], &huka_sisuu[i][1], &huka_sisuu[i][2],  
  &huka_sisuu[i][3], &huka_sisuu[i][4]);

* **fseek**  
**ファイルポインタの位置を指定した位置に移動させる**  
～～～～～～～～～～～～～～～～～～～～～～～～～  
fp = fopen("keisoku.tbl", "r+b");  
fptr = (codedata_tbl[import_tbl.kaiin_code - 1] - 1)  
        \* sizeof(struct KEISOKU_TBL);  
fseek(fp, fptr, SEEK_SET);  
fwrite(&import_tbl, sizeof(struct KEISOKU_TBL), 1, fp);  

* **toupper**  
**小文字を大文字に変換する**  
～～～～～～～～～～～～～～～～～～～～～～～～～  
toupper(work[0]) == 'L'

* **printf**  
**表示桁数は<全体の幅>.<小数点以下の幅>で指定する。**  
**<小数点以下の幅>は、文字列の場合には最大文字数の意味になる。**  
～～～～～～～～～～～～～～～～～～～～～～～～～  
printf( "\n   %2d %4.4s", i + 1,  
    &sort_keisoku_tbl[ i ].max_date[ 0 ]);

* **fseek**  
**ファイルポインタの位置を指定した位置に移動させる**  
～～～～～～～～～～～～～～～～～～～～～～～～～  
fopen->freadでファイルポインタは移動するので、fread後に  
fwriteするときはファイルポインタを変更する必要がある。

* **割り算時の小数点表示**  
doble average  
average = (double)sum/(double)cnt;

* **その他注意点**  
・ポインタと実数の間違い  
・ファイルクローズし忘れ  
・変数の初期化(必要な変数のみ)  
・割り算(0で割らないこと)   

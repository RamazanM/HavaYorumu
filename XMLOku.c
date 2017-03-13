/*
Rüzgar hızı çekmede sorun

*/

#include <mxml.h>
#include "XMLHavaDurumuAl.c"

struct Hava{
  int sicaklik; //Şu anki sıcaklık değeri
  int ruzgar;   //Şu anki rüzgar hızı
  int durum;    //Hava durumu kodu
  char *mesaj;
  char *ikon;
} hava;

typedef struct Durum durum;
struct  Durum{  //durum isimli yapımız
  //int id;         //id'si
  int min_sicaklik;   //kontrol edilecek minimum sıcaklık değeri, NULL ise rüzgar hızını kontrol et
  int max_sicaklik;   //kontrol edilecek maksimum sıcaklık değeri, NULL ise rüzgar hızını kontrol et
  int min_ruzgar_hizi;//kontrol edilecek rüzgar hızı değeri, "     "        "    "     "
  int max_ruzgar_hizi;//kontrol edilecek rüzgar hızı değeri, "     "        "    "     "
  char *mesaj;        //Bu şartları sağladığında verilecek mesaj.
  durum * next;        //bir sonraki durum node'unun pointer'ı.
};

durum *durumlar;

void kodCozumle(int kod);

int HavaDurumunuDoldur(){
  //printf("Deneme\n" );
  HavaDurumuCek();
  FILE *dosya;
  static const char *dosyaAdi="havadurumu.xml"; //Verilerin okunacak olduğu dosyanın adı
  mxml_node_t *anaNode;
  dosya=fopen(dosyaAdi,"r");
  if(!dosya)printf("Dosya Okuma Hatası\n");
  anaNode=mxmlLoadFile(NULL,dosya,MXML_TEXT_CALLBACK);
  mxml_node_t *deger;

  deger=mxmlFindPath(anaNode,"weather/curren_weather/temp/");
  if(mxmlGetText(deger,0)!=NULL)
    hava.sicaklik=atoi(mxmlGetText(deger,0));
  else printf("Hata:Sıcaklık okunamadı(İnternet Bağlantınızı Kontrol Edin)\n");
  deger=mxmlFindPath(anaNode,"weather/curren_weather/wind/speed/");
  if(mxmlGetText(deger,0)!=NULL)
    hava.ruzgar=atoi(mxmlGetText(deger,0));

    printf("%s\n",mxmlGetText(deger,0) );
  deger=mxmlFindPath(anaNode,"weather/curren_weather/weather_code/");
  if(mxmlGetText(deger,0)!=NULL)
    hava.durum=atoi(mxmlGetText(deger,0));



    return 1;
}

int DurumlariDoldur(){

  FILE *dosya;                                //Dosya işlemleri
  static const char *dosyaAdi="durumlar.xml"; //Verilerin okunacak olduğu dosyanın adı
  dosya=fopen(dosyaAdi,"r");                  //Dosyayı aç.

  mxml_node_t *anaNode;                       //XML dosyasının temel node'u
  anaNode=mxmlLoadFile(NULL,dosya,MXML_TEXT_CALLBACK);//Ana nodea dosyayı aktar.
  printf("deneme\n" );
  mxml_node_t *seciliNode;                   //Node'lar arasında yatay gezeceğimiz değişken.
  mxml_node_t *tempNode;                     //Node'lar arasında dikey gezmemizi sağlayacak geçici node.
  seciliNode=anaNode->child;                 //En tepedeki node'un içine giriyoruz.

  durumlar=(durum*)calloc(1,sizeof(durum));
  durum *gezici=durumlar;
  while(seciliNode!=NULL){       //Eğer seçili node boş değilse

    tempNode=mxmlFindPath(seciliNode,"sicaklik/min/");         //XML Dosyasından çekilen değerleri gerekli değişkenlere ata.
    if(mxmlGetText(tempNode,0)!=NULL)
     gezici->min_sicaklik=atoi(mxmlGetText(tempNode,0));

    tempNode=mxmlFindPath(seciliNode,"sicaklik/max/");
    if(mxmlGetText(tempNode,0)!=NULL)
    gezici->max_sicaklik=atoi(mxmlGetText(tempNode,0));

    tempNode=mxmlFindPath(seciliNode,"ruzgar/min/");
    if(mxmlGetText(tempNode,0)!=NULL)
    gezici->min_ruzgar_hizi=atoi(mxmlGetText(tempNode,0));

    tempNode=mxmlFindPath(seciliNode,"ruzgar/max/");
    if(mxmlGetText(tempNode,0)!=NULL)
    gezici->max_ruzgar_hizi=atoi(mxmlGetText(tempNode,0));

    tempNode=mxmlFindPath(seciliNode,"mesaj/");
    gezici->mesaj=(char*)mxmlGetText(tempNode,0);

    gezici->next=(durum*)calloc(1,sizeof(durum));
    gezici=durumlar->next;
    seciliNode=seciliNode->next; //Bir sonraki node'a geç.
  }
  kodCozumle(hava.durum);
return 1;
}

const char* getfield(char* line, int num){
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ","))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}


void kodCozumle(int kod) {
FILE *dosya;
dosya=fopen("mesaj_ikon.csv","r");
if(dosya!=NULL)printf("Dosya acildi");
char satir[300];

while (fgets(satir,300,dosya)) {
  char *gecici=strdup(satir);
  if(atoi((char*)getfield(gecici,1))==kod){
    printf("asd:%s\n",getfield(gecici,3) );
  }


}}

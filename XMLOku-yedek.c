#include <mxml.h>
#include "XMLHavaDurumuAl.c"

struct Hava{
  int sicaklik; //Şu anki sıcaklık değeri
  int ruzgar;   //Şu anki rüzgar hızı
  int durum;    //Hava durumu kodu
} hava;

typedef struct Durum durum;
struct  Durum{  //durum isimli yapımız
  int id;         //id'si
  int min_sicaklik;   //kontrol edilecek minimum sıcaklık değeri, NULL ise rüzgar hızını kontrol et
  int max_sicaklik;   //kontrol edilecek maksimum sıcaklık değeri, NULL ise rüzgar hızını kontrol et
  int min_ruzgar_hizi;//kontrol edilecek rüzgar hızı değeri, "     "        "    "     "
  int max_ruzgar_hizi;//kontrol edilecek rüzgar hızı değeri, "     "        "    "     "
  char *mesaj;        //Bu şartları sağladığında verilecek mesaj.
  durum * next;        //bir sonraki durum node'unun pointer'ı.
};

durum *durumlar;

int HavaDurumunuDoldur(){
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
  deger=mxmlFindPath(anaNode,"weather/curren_weather/weather_code/");
  if(mxmlGetText(deger,0)!=NULL)
    hava.durum=atoi(mxmlGetText(deger,0));
  printf("Denemne:%d\n",hava.sicaklik);
}

int DurumlariDoldur(){
  FILE *dosya;
  static const char *dosyaAdi="durumlar.xml"; //Verilerin okunacak olduğu dosyanın adı
  mxml_node_t *anaNode;                       //XML dosyasının temel node'u
  dosya=fopen(dosyaAdi,"r");                  //Dosyayı aç.
  anaNode=mxmlLoadFile(NULL,dosya,MXML_TEXT_CALLBACK);//Ana nodea dosyayı aktar.
  mxml_node_t *seciliNode;                   //Node'lar arasında yatay gezeceğimiz değişken.
  seciliNode=anaNode->child;                 //En tepedeki node'un içine giriyoruz.
  int toplamDurum=0;             //Toplamdaki durum sayısını bulmak için kullandığım değişken.
  while(seciliNode!=NULL){       //Eğer seçili node boş değilse
    toplamDurum++;               //Durum sayısını bir arttır
    seciliNode=seciliNode->next; //Bir sonraki node'a geç.
  }
  printf("%d\n",toplamDurum );   //Toplam durum sayısını yazdır.

  durumlar=(durum *) calloc(toplamDurum,sizeof(durum)); //Durumlardan oluşan bir dizi oluştur.
  seciliNode=anaNode->child; //Seçili node'u resetle.
  mxml_node_t *tempNode;     //Node'lar arasında dikey gezmemizi sağlayacak geçici node.

  int i; //Sayaç değişkeni
  durum *seciliDurum; //Durum dizisini doldurmak için elimde tuttuğum geçici durum değişkeni.
  seciliDurum=durumlar;
  for(i=0;i<toplamDurum;i++){  //Tüm durumları for ile gez

    seciliDurum->id=i;  //Durum id'si sayaça eşit olacak.

    tempNode=mxmlFindPath(seciliNode,"sicaklik/min/");         //XML Dosyasından çekilen değerleri gerekli değişkenlere ata.
    if(mxmlGetText(tempNode,0)!=NULL)
     seciliDurum->min_sicaklik=atoi(mxmlGetText(tempNode,0));

    tempNode=mxmlFindPath(seciliNode,"sicaklik/max/");
    if(mxmlGetText(tempNode,0)!=NULL)
    seciliDurum->max_sicaklik=atoi(mxmlGetText(tempNode,0));

    tempNode=mxmlFindPath(seciliNode,"ruzgar/min/");
    if(mxmlGetText(tempNode,0)!=NULL)
    seciliDurum->min_ruzgar_hizi=atoi(mxmlGetText(tempNode,0));

    tempNode=mxmlFindPath(seciliNode,"ruzgar/max/");
    if(mxmlGetText(tempNode,0)!=NULL)
    seciliDurum->max_ruzgar_hizi=atoi(mxmlGetText(tempNode,0));

    tempNode=mxmlFindPath(seciliNode,"mesaj/");
    seciliDurum->mesaj=(char*)mxmlGetText(tempNode,0);

    seciliNode=seciliNode->next;          //Bir sonraki node'a geç.
    seciliDurum->next=seciliDurum+1;      //Next node'unu bir sonraki durum node'una eşitle.
    seciliDurum=seciliDurum->next;        //Bir sonraki durumu seç.
  }
}

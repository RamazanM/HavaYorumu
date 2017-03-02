/*
Konya için link: http://www.myweather2.com/developer/forecast.ashx?uac=Xi6lMrUzQg&output=xml&query=37.990073,32.516361
*/
#include <curl/curl.h>

static size_t veriYaz(void *ptr, size_t boyut,size_t elemanSayisi,void *akis){  //CURL'da veriler buffer'lı bir şekilde yazıldığı için veri yazma fonksiyonu oluşturmalıyız.
  size_t yazilan=fwrite(ptr,boyut,elemanSayisi,(FILE *) akis);                  //Standart kütüphanede bulunan dosyaya veri yazma komutu.
  return yazilan; //Başarıyla yazılan eleman sayısını döndürür.
}

void HavaDurumuCek(){
  CURL *curl_tutucu;                            //CURL ayarlamalarını tutacak olan CURL pointer'ı
  static const char *dosyaAdi="havadurumu.xml"; //Verilerin yazılacak olduğu dosyanın adı
  FILE *dosya;                                  //Dosya değişkeni.

  curl_global_init(CURL_GLOBAL_ALL);          //CURL kütüphanesindeki bütün ayar bayraklarını kapsayacak şekilde hazırla.
  curl_tutucu = curl_easy_init();             //Tutucuyu hazırla.
  curl_easy_setopt(curl_tutucu,CURLOPT_URL,"http://www.myweather2.com/developer/forecast.ashx?uac=Xi6lMrUzQg&output=xml&query=37.990073,32.516361");  //Verilerin çekileceği URL'i ayarla.
  curl_easy_setopt(curl_tutucu,CURLOPT_WRITEFUNCTION,veriYaz);  //Veriyi yazmak için kullanacağımız fonksiyon.

  dosya=fopen(dosyaAdi,"wb"); //Dosya değişkenine açılan dosyayı ata.
  if(dosya){                  //Eğer dosya başarıyla açıldıysa..
    curl_easy_setopt(curl_tutucu,CURLOPT_WRITEDATA,dosya);  //Verilerin yazılacak olduğu dosya değişkenini ayarla.
    curl_easy_perform(curl_tutucu); //CURL'u çalıştır.
    fclose(dosya);  //Dosyayı kapat.
  }
  curl_easy_cleanup(curl_tutucu); //Tutucu'yu temizle.
  printf("Hava Durumu Güncellendi.\n");

}

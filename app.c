#include<stdio.h>

/*
  *http://www.myweather2.com benzeri bir siteden o anki/günki hava durumu değerleri (sıcaklık ve rüzgar hızı) çekilecek.

  *Şartları belirttiğim bir xml dosyası olacak (Şartlar alttaki durum structındaki gibi olacak).

  *http://xmlsoft.org/examples/index.html yukarıdaki API'den ve yukarıda belirtilen şartlar xml'inden gelen verileri
   kullanabilmek için libxml2 kütüphanesi kullanılacak.

  *https://developer.gnome.org/gtk3/stable/index.html Grafiksel arayüz için GTK+ kullanılacak.

   Belirtilen hava şartları doğrultusunda rastgele mesajlar sunan uygulama.

*/



struct  durum{  //durum isimli yapımız
  int id,         //id'si
  int min_sicaklik,   //kontrol edilecek minimum sıcaklık değeri, NULL ise rüzgar hızını kontrol et
  int max_sicaklik,   //kontrol edilecek maksimum sıcaklık değeri, NULL ise rüzgar hızını kontrol et
  int min_ruzgar_hizi,//kontrol edilecek rüzgar hızı değeri, "     "        "    "     "
  int max_ruzgar_hizi,//kontrol edilecek rüzgar hızı değeri, "     "        "    "     "
  char mesaj[100];
  durum * next    //bir sonraki durum node'unun pointer'ı.
};
typedef struct durum durum;

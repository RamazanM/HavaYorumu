#include<stdio.h>
#include "XMLOku.c"
/*
  *http://www.myweather2.com benzeri bir siteden o anki/günki hava durumu değerleri (sıcaklık ve rüzgar hızı) çekilecek.

  *Şartları belirttiğim bir xml dosyası olacak (Şartlar alttaki durum structındaki gibi olacak).

  *http://xmlsoft.org/examples/index.html yukarıdaki API'den ve yukarıda belirtilen şartlar xml'inden gelen verileri
   kullanabilmek için libxml2 kütüphanesi kullanılacak.

  *https://developer.gnome.org/gtk3/stable/index.html Grafiksel arayüz için GTK+ kullanılacak.

   Belirtilen hava şartları doğrultusunda rastgele mesajlar sunan uygulama.

*/



int main(int argc, char const *argv[]) {
  HavaDurumunuDoldur();
  DurumlariDoldur();
  while (durumlar->next!=NULL) {
    printf("%s\n",durumlar->mesaj );
    durumlar=durumlar->next;
  }
  return 0;
}

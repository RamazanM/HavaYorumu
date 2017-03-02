#include<stdio.h>
#include "XMLOku.c"
/*
  *http://www.myweather2.com benzeri bir siteden o anki/günki hava durumu değerleri (sıcaklık ve rüzgar hızı) çekilecek.

  *Şartları belirttiğim bir xml dosyası olacak (Şartlar alttaki durum structındaki gibi olacak).

  *https://www.msweet.org/documentation/project3/Mini-XML.html#mxml_node_s
   yukarıdaki API'den ve yukarıda belirtilen şartlar xml'inden gelen verileri
   kullanabilmek için minixml kütüphanesi kullanılacak.

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

while(durumlar->next!=NULL){
  if( hava.sicaklik<=durumlar->max_sicaklik &&
      hava.sicaklik>=durumlar->min_sicaklik ){

        if(durumlar->min_ruzgar_hizi == NULL && durumlar->max_ruzgar_hizi == NULL){
          //Sadece sıcaklık şartı var
        }
        else{
          //Hem sıcaklık hem rüzgar şartı var
        }
      }
    else{

    }

}

  return 0;
}

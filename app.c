#include<stdio.h>
#include "XMLOku.c"
#include "GUI.c"
/*
  *http://www.myweather2.com benzeri bir siteden o anki/günki hava durumu değerleri (sıcaklık ve rüzgar hızı) çekilecek.

  *Şartları belirttiğim bir xml dosyası olacak (Şartlar alttaki durum structındaki gibi olacak).

  *https://www.msweet.org/documentation/project3/Mini-XML.html#mxml_node_s
   yukarıdaki API'den ve yukarıda belirtilen şartlar xml'inden gelen verileri
   kullanabilmek için minixml kütüphanesi kullanılacak.

  *https://developer.gnome.org/gtk3/stable/index.html Grafiksel arayüz için GTK+ kullanılacak.

   Belirtilen hava şartları doğrultusunda rastgele mesajlar sunan uygulama.

       gcc app.c -o deneme.exe -lcurl -lmxml
       gcc `pkg-config --cflags gtk+-3.0` GUI.c -o Gui.exe `pkg-config --libs gtk+-3.0`
       gcc HavaYorumu/app.c -o deneme.exe -lcurl -lmxml `pkg-config --cflags gtk+-3.0``pkg-config --libs gtk+-3.0`
*/



int main(int argc, char const *argv[]) {
  HavaDurumunuDoldur();
  printf("Deneme\n" );
  DurumlariDoldur();

  durum *uygunSartlar=(durum*)malloc(sizeof(durum));
  durum *gezici=(durum*)malloc(sizeof(durum));


do {
  if( hava.sicaklik<=durumlar->max_sicaklik &&
      hava.sicaklik>=durumlar->min_sicaklik &&

      hava.ruzgar<=durumlar->max_ruzgar_hizi &&
      hava.ruzgar>=durumlar->min_ruzgar_hizi){
        //Hem sıcaklık hem rüzgar şartları sağlandıysa
        *gezici=*durumlar;                          //Durumlar değişkenini kopyala
        gezici->next=(durum*)malloc(sizeof(durum)); //Gezici pointer'ın next'inde yer ayır
        uygunSartlar=gezici;                        //Uygun Şartlar dizisine geziciyi ata
        gezici=uygunSartlar->next;                  //geziciyi uygun şartların bir sonraki elemanı yap.
      }
  else if(hava.sicaklik<=durumlar->max_sicaklik &&
          hava.sicaklik>=durumlar->min_sicaklik){
            //Sadece sıcaklık şartları sağlandıysa
            *gezici=*durumlar;
            gezici->next=(durum*)malloc(sizeof(durum));
            uygunSartlar=gezici;
            gezici=uygunSartlar->next;
          }
  else if(hava.ruzgar<=durumlar->max_ruzgar_hizi &&
          hava.ruzgar>=durumlar->min_ruzgar_hizi){
            //Sadece rüzgar şartları sağlandıysa
            *gezici=*durumlar;
            gezici->next=(durum*)malloc(sizeof(durum));
            uygunSartlar=gezici;
            gezici=uygunSartlar->next;
          }
 durumlar=durumlar->next;

} while(durumlar->next!=NULL);

GtkApplication *app;
int status;
app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
status = g_application_run (G_APPLICATION (app), 0, NULL);
g_object_unref (app);

return status;

  return 0;
}

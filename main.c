#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void anaMenu();
void biletSatis();
void koltukGoster();
void koltukDegistir();
int musteriTcKontrol(int tcNo_2);

struct Musteri
{
    char ad[20];
    char soyad[20];
    int tc;
};

struct Koltuk
{
    int dolu;
    int numara;
    struct Musteri Musteri_Bilgileri
} Koltuk_Bilgileri[100];


int main()
{
    FILE *dd;
    int i, koltukNo_1, tcNo_1;
    char temp1[20] = {0}, temp2[20] = {0}, temp3[20] = {0}, temp4[20] = {0}, ad[20] = {0}, soyad[20] = {0};

    // odalarin doluluklarina sifir ataniyor ve numaralar yerlestiriliyor
    for ( i = 0; i < 100; i++)
    {
        Koltuk_Bilgileri[i].dolu = 0;
        Koltuk_Bilgileri[i].numara = i + 1;
    }

    // dosyadaki bilgiler okunup structa yerlestiriliyor
    dd = fopen("KoltukBiletDosyaFormu.txt", "r");

    if (dd == NULL)
    {
        printf("Dosya Hatasi!\n");
    }

    else
    {
        // Koltuk_No            TC           Ad         Soyad   kelimeleri cope atiliyor
        fscanf(dd, "%s%s%s%s", temp1, temp2, temp3, temp4);
        while ((fscanf(dd, "%d%d%s%s", &koltukNo_1, &tcNo_1, ad, soyad)) != EOF)
        {
            Koltuk_Bilgileri[koltukNo_1 - 1].dolu = 1;
            Koltuk_Bilgileri[koltukNo_1 - 1].Musteri_Bilgileri.tc = tcNo_1;
            strcpy(Koltuk_Bilgileri[koltukNo_1 - 1].Musteri_Bilgileri.ad, ad);
            strcpy(Koltuk_Bilgileri[koltukNo_1 - 1].Musteri_Bilgileri.soyad, soyad);
        }
        fclose(dd);
    }

    printf("\nBilet Programina Hos Geldiniz!\n");

    anaMenu();    

    printf("\n\n");
    return 0;
}

void anaMenu()
{
    int islem = 0;

    while (islem != 4)
    {
        printf("\n1-Bilet satis\n");
        printf("2-Koltuk goster\n");
        printf("3-Koltuk degistir\n");
        printf("4-Cikis\n");
        printf("Bir islem seciniz: ");
        scanf("%d", &islem);

        switch (islem)
        {
            case 1:
                biletSatis();
                break;
            case 2:
                koltukGoster();
                break;
            case 3:
                koltukDegistir();
                break;
            case 4:
                return;
            default:
                break;
        }
    }

}

void biletSatis()
{
    int tcNo_2, koltukNo_2, flag_1 = -1;
    char ad_2[20] = {0}, soyad_2[20] = {0}, dosyaBosMuKontrol[20] = {0};

    printf("\nMusteri tc giriniz: ");
    scanf("%d", &tcNo_2);

    int yanit = musteriTcKontrol(tcNo_2);

    if (yanit == 1)
    {
        printf("Bu musteri zaten burada\n");
        return;
    }

    printf("Koltuk numarasi giriniz: ");
    scanf("%d", &koltukNo_2);
    
    if (Koltuk_Bilgileri[koltukNo_2 - 1].dolu == 1)
    {
        printf("Koltuk dolu!\n");
        return;
    }

    printf("Musteri adini giriniz: ");
    scanf("%s", ad_2);

    printf("Musteri soyadini giriniz: ");
    scanf("%s", soyad_2);

    Koltuk_Bilgileri[koltukNo_2 - 1].dolu = 1;
    Koltuk_Bilgileri[koltukNo_2 - 1].Musteri_Bilgileri.tc = tcNo_2;
    strcpy(Koltuk_Bilgileri[koltukNo_2 - 1].Musteri_Bilgileri.ad, ad_2);
    strcpy(Koltuk_Bilgileri[koltukNo_2 - 1].Musteri_Bilgileri.soyad, soyad_2);

    FILE *dd;

    // dosyanin ici tamamen bos mu kontrol ediliyor, bossa basliklar yaziliyor
    dd = fopen("KoltukBiletDosyaFormu.txt", "r");

    if (dd == NULL)
    {
        printf("Dosya Hatasi!\n");
    }

    else
    {
        fscanf(dd, "%s", dosyaBosMuKontrol);
        // ilk kelime Koltuk_No ise dosya halihazirda doludur, değilse bostur.
        if (strcmp(dosyaBosMuKontrol, "Koltuk_No") != 0)
        {
            flag_1 = 0;  // Dosya bos.
        }
        else
            flag_1 = 1;
        fclose(dd);
    }
    
    // dosyaya yeni koltuk bilgileri yaziliyor
    dd = fopen("KoltukBiletDosyaFormu.txt", "a");

    if (dd == NULL)
    {
        printf("Dosya Hatasi\n");
    }

    else
    {
        if (flag_1 != 1)  // yani dosya bossa
        {
            fprintf(dd, "Koltuk_No            TC           Ad         Soyad\n");
        }
        fprintf(dd, "%-20d%-13d%-12s%s\n", koltukNo_2, tcNo_2, ad_2, soyad_2);
        fclose(dd);
    }

    printf("\nBilet satisi basarili!\n");
}

void koltukGoster()
{
    int i, koltukNo_2;

    printf("\nKoltuk numarasini giriniz: ");
    scanf("%d", &koltukNo_2);

    if (Koltuk_Bilgileri[koltukNo_2 - 1].dolu == 0)
    {
        printf("Koltuk bos!\n");
        return;
    }

    printf("Koltuk numarasi: %d\n", koltukNo_2);
    printf("Musteri tc: %d\n", Koltuk_Bilgileri[koltukNo_2 - 1].Musteri_Bilgileri.tc);
    printf("Musteri ad: %s\n", Koltuk_Bilgileri[koltukNo_2 - 1].Musteri_Bilgileri.ad);
    printf("Musteri soyad: %s\n", Koltuk_Bilgileri[koltukNo_2 - 1].Musteri_Bilgileri.soyad);
}

void koltukDegistir()
{
    int tcNo_2, eskiKoltuk, yeniKoltuk, i;

    printf("\nKoltugunu degistirmek istediginiz musterinin tc'sini giriniz: ");
    scanf("%d", &tcNo_2);

    int yanit = musteriTcKontrol(tcNo_2);

    if (yanit == 0)
    {
        printf("Boyle bir musteri bulunmamakta!\n");
        return;
    }

    printf("Hangi koltuga gecmek istiyor: ");
    scanf("%d", &yeniKoltuk);
    
    if (Koltuk_Bilgileri[yeniKoltuk - 1].dolu == 1)
    {
        printf("Koltuk dolu!\n");
        return;
    }

    // girilen tc'nin oturdugu koltugu tespit ediyor
    for ( i = 0; i < 100; i++)
    {
        if (Koltuk_Bilgileri[i].dolu == 1)
        {
            if (Koltuk_Bilgileri[i].Musteri_Bilgileri.tc == tcNo_2)
            {
                eskiKoltuk = i + 1;
                break;
            }
        }
    }

    // yeni koltuk dolduruluyor
    strcpy(Koltuk_Bilgileri[yeniKoltuk - 1].Musteri_Bilgileri.ad, Koltuk_Bilgileri[eskiKoltuk - 1].Musteri_Bilgileri.ad);
    strcpy(Koltuk_Bilgileri[yeniKoltuk - 1].Musteri_Bilgileri.soyad, Koltuk_Bilgileri[eskiKoltuk - 1].Musteri_Bilgileri.soyad);
    Koltuk_Bilgileri[yeniKoltuk - 1].Musteri_Bilgileri.tc = tcNo_2;

    // eski koltuk boşaltılıyor
    strcpy(Koltuk_Bilgileri[eskiKoltuk - 1].Musteri_Bilgileri.ad, "");
    strcpy(Koltuk_Bilgileri[eskiKoltuk - 1].Musteri_Bilgileri.soyad, "");
    Koltuk_Bilgileri[eskiKoltuk - 1].Musteri_Bilgileri.tc = 0;

    Koltuk_Bilgileri[yeniKoltuk - 1].dolu = 1;
    Koltuk_Bilgileri[eskiKoltuk - 1].dolu = 0;

    // dosya guncelleniyor
    FILE *dd;

    // write modunda, overwrite yapiliyor
    dd = fopen("KoltukBiletDosyaFormu.txt", "w");

    if (dd == NULL)
    {
        printf("Dosya Hatasi!\n");
    }

    else
    {
        int i_2;  // sanirim int i olarak da tanimlasaydim bellekte yeni bir yer acacakti.

        fprintf(dd, "Koltuk_No            TC           Ad         Soyad\n");

        for ( i_2 = 0; i_2 < 100; i_2++)
        {
            if (Koltuk_Bilgileri[i_2].dolu == 1)
            {
                fprintf(dd, "%-20d%-13d%-12s%s\n", Koltuk_Bilgileri[i_2].numara, Koltuk_Bilgileri[i_2].Musteri_Bilgileri.tc,
                    Koltuk_Bilgileri[i_2].Musteri_Bilgileri.ad, Koltuk_Bilgileri[i_2].Musteri_Bilgileri.soyad);
            }
            
        }
        fclose(dd);
    }
    
    printf("Koltuk degistirme islemi basarili!\n");
}

int musteriTcKontrol(int tcNo_2)
{
    int i;

    for ( i = 0; i < 100; i++)
    {
        if (Koltuk_Bilgileri[i].dolu == 1)
        {
            if (Koltuk_Bilgileri[i].Musteri_Bilgileri.tc == tcNo_2)
            {
                return 1;
            }
            
        }
    }
    return 0;
}
/*
Ek olarak fonskiyonlarin sonuna:
printf("\nAna menuye donmek icin ENTER tusuna basiniz");
int C7;
while ((C7 = getchar()) != '\n' && C7 != EOF);
getchar();
yazilabilirdi

onceden 'boyle bir musteri var mi' islemini dosya icinde ararken soyle bir yontem izlemistim. Bu yontemde dosya
Koltuk numarasini giriniz: 5
Koltuk numarasi: 5
Musteri tc: 123
Musteri ad: Ahmet
Musteri soyad: Tas
seklindeydi.
Haliyle st2 = 'tc:' oldugunda int1'e atanacak sey tc numarasi olacakti ve bu sekilde boyle bir musteri var mi bakiliyordu:
int musteriTcKontrol(int tcNo_2)
{
    FILE *dd;
    int i, int1;
    char st1[20] = {0}, st2[20] = {0};

    if ((dd = fopen("KoltukBiletDosyaFormu.txt", "r")) == NULL)
    {
        printf("Dosya hatasi\n");
    }
    else
    {
        while ((fscanf(dd, "%s%s%d", st1, st2, &int1)) != EOF)
        {
            if (strcmp(st2, "tc:") == 0)
            {
                if (int1 == tcNo_2)
                {
                    return 1;
                }
                
            }
...
...
*/

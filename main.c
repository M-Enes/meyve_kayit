#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEYVE_ISIM_UZUNLUGU 20

struct meyve {
    unsigned int id;
    char isim[MEYVE_ISIM_UZUNLUGU];
    float fiyat;
    struct meyve *back;
    struct meyve *next;
};


void MeyveListele(struct meyve *);

void MeyveEkle(unsigned int *, struct meyve *);

void MeyveSil(struct meyve *);

void MeyveBul(struct meyve *);

void MeyveDuzenle(struct meyve *);

void DosyadanOku(unsigned int *, struct meyve *);

void DosyayaKaydet(unsigned int *, struct meyve *);

int main() {

    unsigned int *sonKullanilanId = (unsigned int *) malloc(sizeof(unsigned int));
    *sonKullanilanId = 0;

    struct meyve *head = (struct meyve *) malloc(sizeof(struct meyve));
    *head = (struct meyve) {};

    DosyadanOku(sonKullanilanId, head);


    char *menu = "\
****MEYVE KAYIT PROGRAMI****\n\n\
    1-meyve ekle \n\
    2-meyve bul \n\
    3-meyve duzenle \n\
    4-meyve sil \n\
    5-meyveleri listele \n\
    6-secenekleri listele\n\
    7-ciki$ \n\n";
    printf("%s", menu);


    secim_ekrani:

    printf("    Seciminizi giriniz: ");

    int secim;
    scanf("%d", &secim);

    switch (secim) {
        case 1:
            MeyveEkle(sonKullanilanId, head);
            DosyayaKaydet(sonKullanilanId, head);
            break;
        case 2:
            MeyveBul(head);
            break;
        case 3:
            MeyveDuzenle(head);
            DosyayaKaydet(sonKullanilanId, head);
            break;
        case 4:
            MeyveSil(head);
            DosyayaKaydet(sonKullanilanId, head);
            break;
        case 5:
            MeyveListele(head);
            break;
        case 6:
            printf("\e[1;1H\e[2J");
            printf("%s\n\n", menu);
            break;
        case 7:
            printf("Ciki$ yapiliyor...\n");
            exit(EXIT_SUCCESS);
        default:
            printf("!-Hatali giri$ yaptiniz\n");
            break;
    }
    goto secim_ekrani;
}

void MeyveListele(struct meyve *head) {
    struct meyve *current = head;

    if (*current->isim == '\0') {
        printf("Listede hiç meyve bulunmamaktadir.\n");
        return;
    }

    printf("      ID  |        ISIM       |  FIYAT\n    ------------------------------------\n");
    while (current != NULL) {
        printf("    %-6d %-20s %.2f\n", current->id, current->isim, current->fiyat);
        current = current->next;
    }

}

void MeyveEkle(unsigned int *sonKullanilanId, struct meyve *head) {
    struct meyve *current = head;

    while (current->next != NULL)
        current = current->next;

    char *isim = (char *) malloc(sizeof(char) * (MEYVE_ISIM_UZUNLUGU + 1));
    float fiyat;

    printf("Eklemek istediginiz meyvenin ismini giriniz: ");
    scanf("%s", isim);

    printf("Eklemek istediginiz meyvenin fiyatını giriniz: ");
    scanf("%f", &fiyat);


    if (*current->isim == '\0') {
        *current = (struct meyve) {.id=++*sonKullanilanId, .fiyat=fiyat, .back=NULL, .next=NULL};

        for (int i = 0; i < MEYVE_ISIM_UZUNLUGU + 1; i++) {
            *(current->isim + i) = isim[i];
        }

    } else {
        current->next = (struct meyve *) malloc(sizeof(struct meyve));
        *current->next = (struct meyve) {.id=++*sonKullanilanId, .fiyat=fiyat, .back = current, .next = NULL};

        for (int i = 0; i < MEYVE_ISIM_UZUNLUGU + 1; i++) {
            *(current->next->isim + i) = isim[i];
        }
    }

    printf("Meyve basariyla eklendi.\n");

}

void MeyveBul(struct meyve *head) {
    struct meyve *current = head;

    char *isim = (char *) malloc(sizeof(char) * (MEYVE_ISIM_UZUNLUGU + 1));

    printf("Aradiginiz meyvenin ismini giriniz: ");
    scanf("%s", isim);

    if (current->isim == (char *) NULL) {
        printf("Listede hiç meyve bulunmamaktadir.\n");
        return;
    }

    while (strcmp(current->isim, isim) != 0) {
        if (current->next == NULL) {
            printf("Aradiginiz isimde meyve bulunamadi.\n");
            return;
        }
        current = current->next;
    }

    printf("meyve id : %d, isim : %s, fiyat : %.2f\n", current->id, current->isim, current->fiyat);

}


void MeyveDuzenle(struct meyve *head) {
    struct meyve *current = head;

    int id;
    printf("Duzenlemek istediginiz meyvenin idsini giriniz: ");
    scanf("%d", &id);

    while (current->id != id) {
        if (current->next == NULL) {
            printf("Aradiginiz idye sahip meyve bulunamadi.\n");
            return;
        }
        current = current->next;
    }

    char *isim = (char *) malloc(sizeof(char) * (MEYVE_ISIM_UZUNLUGU + 1));
    float fiyat;

    printf("Meyvenin yeni ismini giriniz (degi$tirmemek icin -1 yaziniz): ");
    scanf("%s", isim);
    if (strcmp(isim, "-1") != 0) *current->isim = *isim;

    printf("Meyvenin yeni fiyatını giriniz (degi$tirmemek icin -1 yaziniz): ");
    scanf("%f", &fiyat);
    if (fiyat != -1) current->fiyat = fiyat;

    printf("Meyve basariyla duzenlendi.\n");

}

void MeyveSil(struct meyve *head) {
    struct meyve *current = head;

    int id;
    printf("Silmek istediginiz meyvenin idsini giriniz: ");
    scanf("%d", &id);

    while (current->id != id) {
        if (current->next == NULL) {
            printf("Aradiginiz idye sahip meyve bulunamadi.\n");
            return;
        }
        current = current->next;
    }

    if (current->next == NULL && current->back == NULL) {
        // single element
        *head = (struct meyve) {};
    } else if (current->next == NULL) {
        // last element
        current->back->next = NULL;
        free(current);
    } else if (current->back == NULL) {
        // first element (head)
        current = head->next;
        free(current->back);
        current->back = NULL;
        *head = *current;
    } else {
        current->back->next = current->next->back;
        free(current);
    }

    printf("Meyve basariyla silindi.\n");

}

void DosyayaKaydet(unsigned int *sonKullanilanId, struct meyve *head) {
    struct meyve *current = head;

    FILE *file;
    file = fopen("./data", "wb");

    if (file == NULL) {
        printf("Dosya olusturulamadi\n");
        return;
    }

    fwrite(sonKullanilanId,sizeof(unsigned int),1,file);
    while (current != NULL) {
        fwrite(current, sizeof(struct meyve), 1, file);
        current = current->next;
    }

    fclose(file);

}

void DosyadanOku(unsigned int *sonKullanilanId, struct meyve *head) {
    struct meyve *current = head;
    struct meyve *meyve = (struct meyve *) malloc(sizeof(struct meyve));

    FILE *file;
    file = fopen("./data", "rb");
    if (file == NULL) {
        printf("Dosya bulunmuyor\n");
        return;
    }

    fread(sonKullanilanId,sizeof(unsigned int), 1,file);

    while (fread(meyve, sizeof(struct meyve), 1, file) == 1) {
        if (meyve != NULL) {
            meyve->back = NULL;
            meyve->next = NULL;
            *current = *meyve;
            current->next = (struct meyve *) malloc(sizeof(struct meyve));
            current->next->back = current;
            current = current->next;
        }
    }

    current->back->next = NULL;
    free(current);

    fclose(file);
}


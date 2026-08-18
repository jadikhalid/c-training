#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <openssl/des.h>

#define MODE_ENCRYPT 0
#define MODE_DECRYPT 1
#define DES_FAILED(stat) ((stat) != 0)

/* Ajuste la parité de la clé DES (parité impaire) */
void local_des_setparity(char *key)
{
    for (int i = 0; i < 8; i++)
    {
        unsigned char b = (unsigned char)key[i];
        int count = 0;
        for (int bit = 1; bit < 8; bit++)
        {
            if (b & (1 << bit))
                count++;
        }
        if ((count % 2) == 0)
            key[i] = (char)(b | 1);
        else
            key[i] = (char)(b & ~1);
    }
}

/* Effectue le chiffrement/déchiffrement ECB sur un tampon en mémoire */
int local_ecb_crypt(char *key, char *buf, unsigned int len, unsigned int mode)
{
    if (len % 8 != 0)
        return -1;

    DES_cblock key_block;
    memcpy(key_block, key, 8);

    DES_key_schedule schedule;
    /* Désactivation temporaire des warnings de dépréciation OpenSSL pour DES */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    if (DES_set_key_checked(&key_block, &schedule) < 0)
        return -1;

    int enc = (mode == MODE_ENCRYPT) ? DES_ENCRYPT : DES_DECRYPT;

    for (unsigned int i = 0; i < len; i += 8)
    {
        DES_ecb_encrypt((DES_cblock *)(buf + i), (DES_cblock *)(buf + i), &schedule, enc);
    }
#pragma GCC diagnostic pop

    return 0;
}

int main(int argc, char *argv[])
{
    char *nom_programme;
    int fichier;
    struct stat etat_fichier;
    size_t taille_fichier;
    char *projection;
    char cle[8] = {0};
    unsigned int mode;
    int retour;

    if (argc != 3)
    {
        fprintf(stderr, "Syntaxe : %s <fichier> <clé>\n", argv[0]);
        exit(1);
    }
    nom_programme = basename(argv[0]);

    if (strcasecmp(nom_programme, "des_decrypte") == 0)
        mode = MODE_DECRYPT;
    else
        mode = MODE_ENCRYPT;

    if ((fichier = open(argv[1], O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }

    if (fstat(fichier, &etat_fichier) != 0)
    {
        perror("fstat");
        exit(1);
    }

    taille_fichier = (size_t)etat_fichier.st_size;
    taille_fichier = ((taille_fichier + 7) >> 3) << 3;

    /* Agrandit la taille physique du fichier sur disque si non multiple de 8 */
    if ((size_t)etat_fichier.st_size < taille_fichier)
    {
        if (ftruncate(fichier, (off_t)taille_fichier) != 0)
        {
            perror("ftruncate");
            exit(1);
        }
    }

    projection = (char *)mmap(NULL, taille_fichier, PROT_READ | PROT_WRITE, MAP_SHARED, fichier, 0);

    if (projection == (char *)MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    close(fichier);

    strncpy(cle, argv[2], 8);
    local_des_setparity(cle);
    retour = local_ecb_crypt(cle, projection, (unsigned int)taille_fichier, mode);

    if (DES_FAILED(retour))
    {
        fprintf(stderr, "Erreur lors du traitement DES\n");
        exit(1);
    }

    munmap(projection, taille_fichier);

    return 0;
}
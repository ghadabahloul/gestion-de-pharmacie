// Console application to manage a pharmacy
// by Ghada Bahloul - 2013
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

void med(void);
void menu(void);
void vente(void);
void comm(void);
void fourn(void);
void about(void);

struct medicament {
	char code_medoc[20] ;
	char nom_medoc[20];
	char categorie[20];
	char date_exp[10];
	float prix;
	int qte_en_stcok;
};

struct medvente {
	char code_medoc[20] ;
	char nom_medoc[20];
	float prix;
	int qte;
	float prix_tot;
};

struct vente {
	int code_vente[20];
	char agent[10];
	char date[11];
	struct medvente mq[10];
	float prix_total;
	int medic_nbr;
};

struct fournisseur {
	char code_fourn[20] ;
	char nom_fourn[50];
	char adresse[50];
	int tel;

};

int count_med()
{
	FILE *fp;
	struct medicament x;
	int compt = 0;
	fp = fopen("Medicament.txt", "rb");
	while (fread(&x, sizeof(x), 1, fp))
		compt++;
	return compt;
};

char* date()
{
	char *d;
	char m[4];
	char j[3];
	char a[5];
	char *f;

	time_t mytime;
	mytime = time(NULL);
	f = (char*) malloc(11);
	d = (char*) malloc(25);
	strcpy(d, ctime(&mytime));
	memcpy( m, &d[4], 3 );
	m[3] = '\0';
	memcpy( j, &d[8], 2 );
	j[2] = '\0';
	memcpy( a, &d[20], 4 );
	a[4] = '\0';
	strcpy(f, j);
	strcat(f, "/");
	strcat(f, m);
	strcat(f, "/");
	strcat(f, a);
	f[11] = '\0';

	return (f);
};





void menu()
{
	char choice;
	printf("\t\t*************************************************");
	printf("\n\t\t  *** GESTION D'UNE PHARMACIE  ***");
	printf("\n\t\t*************************************************");
	printf("\n\n\n\n\n\n\n");
	printf("\t\t 1.MEDICAMENT");
	printf("\n\t\t 2.VENTE");
	printf("\n\t\t 3.COMMANDE");
	printf("\n\t\t 4.FOURNISSEUR");
	printf("\n\t\t 5.A PROPOS DU PROGRAMME");
	printf("\n\t\t 0.EXIT");
	printf("\n\n\t ENTRER VOTRE CHOIX: ");
	fflush(stdin);
	choice = getche();

	switch (choice)
	{
	case '1':
		med();
		break;
	case '2':
		vente();
		break;
	case '3':
		comm();
		break;
	case '4':
		fourn();
		break;
	case '5':
		about();
		break;
	case '0':
		exit(1);
	}
}

void main()
{
	int i, logic;
	char iden[10], tab_user[4][10] = {"JAWHER", "jawher", "ghada", "GHADA"};
	do
	{
		logic = 0;
		printf("\n\n\t\tSAISISSEZ VOTRE IDENTIFIANT  : ");
		scanf("%s", iden);
		printf("\n\n  ");

		for (i = 0; i < 4; i++)
		{
			if (strcmp(iden, tab_user[i]) == 0)
			{
				logic = 1;
				break;
			}
		}
	} while (logic == 0);
	menu();
}

/* Medicament */

void med()
{
	char categ_medoc[3][20] = {"sirop   ", "injection", "pillule"};
	char nom_agent[3][20] = {"Lotfi  ", "Ablahmid", "Mounira"};

	struct medicament tabmedic[10];
	struct medicament m, in;
	FILE *fp, *tp, *fpv, *ft;
	int ch;
	int j = 1;
	char c;
	char mnom[20];
	int aux, exist;
	char aux_code[20];

	char another;
	int iF = 0;
	long int recsize;

	fp = fopen("Medicament.txt", "rb+");
	if (fp == NULL)
	{
		fp = fopen("Medicament.txt", "wb+");
		if (fp == NULL)
		{
			puts("\n on peut pas ouvrir le fichier ");
			exit(1);
		}
	}
	recsize = sizeof(m);
	while (1)
	{
		printf("\n ");
		printf("\n\n\t\t\t MEDICAMENT ");
		printf("\n");
		printf("\n\t\t1.AJOUTER UN NOUVEAU MEDICAMENT ");
		printf("\n\t\t2.POUR MODIFIER UN MEDICAMENT");
		printf("\n\t\t3.POUR RECHERCHER PAR NOM");
		printf("\n\t\t4.POUR RECHERCHER PAR REFERENCE");
		printf("\n\t\t5.POUR AFFICHER TOUS LES MEDICAMENT ");
		printf("\n\t\t6.POUR SUPPRIMER UN MEDICAMENT");
		printf("\n\t\t7.POUR RETOURMER AU MENU ");
		printf("\n\n\t\tENTRER VOTRE CHOIX  ");
		fflush(stdin);
		ch = getche();

		switch (ch)
		{
		case '1':
			fseek(fp, 0, SEEK_END);
			another = 'Y';
			while (another == 'Y' || another == 'y')
			{
w:
				printf("\n\n\nENTRER LA REFERENCE: ");
				scanf("%s", aux_code);
				rewind(fp);

				while (fread(&m, recsize, 1, fp) == 1)
				{

					if (strcmp(aux_code, m.code_medoc) == 0)
					{
						iF = 1;
						printf("\n\t\tCETTE REFERENCE EXISTE DEJA  ENTRER UNE AUTRE :");
						goto w;
					}
				}
				if (iF == 0 || fread(&m, recsize, 1, fp) == 0)
				{
					fseek (fp, 0, SEEK_END);
					strcpy(m.code_medoc, aux_code);
					fflush(stdin);
					printf("\nENTER LE NOM   :-> ");
					scanf("%s", m.nom_medoc);
					fflush(stdin);
					printf("\n ENTER LA CATEGORIE   0.'sirop'  1.'injection'   2.'pillule'         :-> ");
					scanf("%d", &aux);
					strcpy(m.categorie, categ_medoc[aux]);
					fflush(stdin);
					printf("\nENTER LA DATE D'EXPIRATION     :->  ");
					scanf("%s", &m.date_exp);
					printf("\nENTER LE PRIX                  :-> ");
					scanf("%f", &m.prix);
					fflush(stdin);
					printf("\nENTER LA QUANTITE              :-> ");
					scanf("%d", &m.qte_en_stcok);
					fflush(stdin);
					fwrite(&m, recsize, 1, fp);
					printf("\n----------------------------------------------------");
					printf("\nVOULEZ VOUS CONTINUER?(Y/N) ");
					fflush(stdin);
					another = getche();
				}
			}
			break;
		case '2':
			another = 'Y';
			while (another == 'Y' || another == 'y')
			{
				printf("\nENTRER LA REFERENCE DU MEDICAMENT A MODIFIER : ");
				scanf("%s", aux_code);
				rewind(fp);
				while (fread(&m, recsize, 1, fp) == 1)
				{
					if (strcmp(m.code_medoc, aux_code) == 0)
					{
						fflush(stdin);
						printf("\nENTRER LE NOUVEAU NOM ");
						scanf("%s", m.nom_medoc);
						printf("\nENTRER LA NOUVELLE DATE DEXPIRATION ");
						scanf("%s", m.date_exp);
						printf("\nENTRER LE NOUVEAU PRIX  ");
						scanf("%f", &m.prix);
						printf("\nENTRER LA NOUVELLE QUANTITEE:\n");
						scanf("%d", &m.qte_en_stcok);
						fflush(stdin);
						fseek(fp, -recsize, SEEK_CUR);
						fwrite(&m, recsize, 1, fp);
						break;
					}
				}
				printf("\n----------------------------------------------------");
				printf("\n MODIFIER UN NOUVEAU MEDICAMENT ?(Y/N): ");
				fflush(stdin);
				another = getche();
			}
			break;
		/*recherche */
		case '3':
			another = 'Y';
			while (another == 'Y' || another == 'y')
			{
				printf("\nENTRER LE NOM DU MEDICAMENT A RECHEERCHER : ");
				gets(mnom);
				rewind(fp);
				while (fread(&m, recsize, 1, fp) == 1)
				{
					if (strcmp(m.nom_medoc, mnom) == 0)
					{
						printf("\n   REF\t NOM    \t FORME   \t DATE_EXP\tPRIX   \tQTE\n");
						printf("\n   %s\t %s\t %s\t %s\t%.2f\t%d", m.code_medoc, m.nom_medoc, m.categorie, m.date_exp, m.prix, m.qte_en_stcok);
					}
				}
				printf("\n    ----------------------------------------------------");
				printf("\nCHERCHER UN AUTRE MEDICAMENT ?(Y/N): ");
				fflush(stdin);
				another = getche();
			}
			break;
		case '4':
			another = 'Y';
			while (another == 'Y' || another == 'y')
			{
				printf("\nENTRER LA REFERENCE DU MEDICAMENT A RECHEERCHER : ");
				gets(aux_code);
				rewind(fp);
				while (fread(&m, recsize, 1, fp) == 1)
				{
					if (strcmp(m.code_medoc, aux_code) == 0)
					{
						printf("\n   REF\t NOM    \t FORME   \t DATE_EXP     \tPRIX   \tQTE\n");
						printf("\n   %s\t %s\t %s\t %s\t%.2f\t%d", m.code_medoc, m.nom_medoc, m.categorie, m.date_exp, m.prix, m.qte_en_stcok);
					}
				}
				printf("\n    ----------------------------------------------------------");
				printf("\nRECHERCHER UN AUTRE (Y/N): ");
				fflush(stdin);
				another = getche();
			}
			break;
		case '5':
			rewind(fp);
			while (fread(&m, recsize, 1, fp) == 1)
			{
				printf("\n   REF\t NOM    \t FORME   \t DATE_EXP   \t PRIX  \t QTE\n");
				printf("   ------------------------------------------------------------------\n");
				for (aux = 0; aux < 10; aux++)
				{
					while (fread(&tabmedic[aux], sizeof(m), 1, fp))
					{
						printf("\n   %d\t %s\t %s\t %s\t%.2f\t%d", j, tabmedic[aux].nom_medoc, tabmedic[aux].categorie, tabmedic[aux].date_exp, tabmedic[aux].prix, tabmedic[aux].qte_en_stcok);
						j++;
					}

				}
				printf("\n    ----------------------------------------------------\n");

			}
			getch();
			break;
		case '6':
			another = 'Y';
			while (another == 'Y' || another == 'y')
			{
				printf("\nENTRER LA REFERENCE DU MEDICAMENT A SUPPRIMER : ");
				scanf("%s", aux_code);
				ft = fopen("temp.txt", "wb+");
				rewind(fp);
				while (fread(&m, recsize, 1, fp) == 1)
				{
					if (strcmp(m.code_medoc, aux_code) != 0)
						fwrite(&m, recsize, 1, ft);
					else
						printf("\nMEDICAMENT A ETE SUPPRIMER AVEC SUCCEE.");
				}

				fclose(fp);
				fclose(ft);
				remove("medicament.txt");
				rename("temp.txt", "medicament.txt");
				fp = fopen("medicament.txt", "rb+");

				printf("\nSUPPRIMER UN AUTRE ?(Y/N): ");
				fflush(stdin);
				another = getche();
			}
			break;
		case '7':
		{
			fclose(fp);

			menu();
		}
		break;
		}
	}
}

/* vente */

void vente()
{
	FILE *fs, *fp;
	char more, c, aux_code[20];
	char id[20], s_name[40];
	int j = 1, iF = 0;

	struct vente v;
	struct vente tab_vente[10];
	struct medicament m;
	int ch, i;
	long int recsize2, recsize3, recsize1;
	char mnom[20], iden[10];
	float s;
	int aux, exist, nbr_m, logic;

	fs = fopen("vente.txt", "rb+");
	if (fs == NULL)
	{
		fs = fopen("vente.txt", "wb+");
		if (fs == NULL)
		{
			puts("\n on peut pas ouvrir le fichier ");
			exit(1);
		}
	}
	recsize2 = sizeof(m);
	recsize3 = sizeof(v);
	while (1)
	{
		printf("\n\t\t\t VENTE ");
		printf("\n\t\t1.EFFECTUER UNE VENTE ");
		printf("\n\t\t2.LISTE DES VENTES");
		printf("\n\t\t3.VERIFIER LES STOCKS.");
		printf("\n\t\t4.RETOUR AU MENU PRINCIALE ");
		printf("\n\n\t\tENTRER VOTRE CHOIX : ");
		fflush(stdin);
		c = getche();

		switch (c)
		{
		case '1':
			strcpy(v.agent, iden);
			//v.code_vente=9; //AUTOINCREMENTé
			strcpy(v.date, date());
			i = 0; s = 0; nbr_m = 0;
			while (1)
			{	nbr_m++;
				do
				{
					printf("\nENTER LE NOM DU MEDICAMENT           :-> ");
					scanf("%s", s_name);
					exist = 1;
					fp = fopen("Medicament.txt", "rb");
					while (fread(&m, recsize2, 1, fp) == 1)
					{
						if (strcmp(m.nom_medoc, s_name) == 0)
						{
							strcpy(v.mq[i].nom_medoc, m.nom_medoc);
							v.mq[i].nom_medoc == m.nom_medoc;
							v.mq[i].prix = m.prix;

							printf("DONNER LA QUANTITE : ");
							scanf("%d", &v.mq[i].qte);
							v.mq[i].prix_tot = v.mq[i].qte * v.mq[i].prix;
							i++;
							fflush(stdin);

							exist = 1;
						}
					}
					fclose(fp);
				} while (exist == 0);

				printf("\n\nVOULEZ VOUS CONTINUER?(Y/N)");
				scanf("%c", &c);
				if (c == 'n' || c == 'N')
				{	for (aux = 0; aux < i; aux++)
						s = s + v.mq[aux].prix_tot;

					v.prix_total = s;
					v.medic_nbr = nbr_m;
					fs = fopen("vente.txt", "ab");
					fwrite(&v, sizeof(v), 1, fs);
					fflush(stdin);
					break;
				}
			}

			for (aux = 0; aux < i; aux++)
				printf("\n  %d    X     %s   %.2f    %.2f ", v.mq[aux].qte, v.mq[aux].nom_medoc, v.mq[aux].prix, v.mq[aux].prix_tot);
			printf("\n---------------------------------------", v.prix_total);
			printf("\n                        Total =  %.2f ", v.prix_total);
			printf("\n ");
			getch();
			break;
		case '2':
			rewind(fs);
			for (aux = 0; aux < 1; aux++)
			{
				while (fread(&tab_vente[aux], sizeof(v), 1, fs))
				{
					printf("\n       %d\t %s       %s        %.2f     ", j, tab_vente[aux].date, tab_vente[aux].agent, tab_vente[aux].prix_total);
					j++;
					printf("\n       --------------------------------------------------------------");
				}
				for (i = 0; i < tab_vente[aux].medic_nbr; i++)
				{
					printf("\n          %d   X   %s       %.2f        %.2f\n", tab_vente[aux].mq[i].qte, tab_vente[aux].mq[i].nom_medoc, tab_vente[aux].mq[i].prix, tab_vente[aux].mq[i].prix_tot);
				}
				printf("\n");
				printf("\n");
			}
			getch();
			break;
		case '3':
			int i;
			FILE *p;
			struct medicament x;
			struct medicament tabmedic[10];
			p = fopen("Medicament.txt", "r");
			printf("\n le stock des medicaments suivants seront bientot epuisees \n \n");
			printf("\n   REF\t  NOM_MED\t ");
			printf("\n ");
			for (i = 0; i < count_med(); i++)
			{
				{
					while (fread(&tabmedic[i], sizeof(x), 1, p))
					{
						if (tabmedic[i].qte_en_stcok < 20)
							printf("\n   %s\t %s\t \n", tabmedic[i].code_medoc, tabmedic[i].nom_medoc);
					}
				}

			}
			getch();
			break;
		case '4':
		{
			fclose(fs);

			menu();
		}
		break;
		}
	}
}

void comm() {

}

/* FOURNISSEUR */

void fourn()
{
	FILE *fi, *fy;
	char a, m;
	char i_name[40], code[20];
	int iF = 0, j = 1;
	long int recsize2;
	struct fournisseur f;

	fi = fopen("fourn.txt", "rb+");
	if (fi == NULL)
	{
		fi = fopen("fourn.txt", "wb+");
		if (fi == NULL)
		{
			puts(" IMPOSSIBLE D'OUVRIR LE FICHIER");
			exit(1);
		}
	}
	recsize2 = sizeof(f);
	while (1)
	{
		printf("\n\t\t\t FOURNISSEUR \n");
		printf("\n\t\t1.AJOUTER UN FOURNISSEUR");
		printf("\n\t\t2.MODIFIER UN FOURNISSEUR");
		printf("\n\t\t3.RECHERCHER ");
		printf("\n\t\t4.LISTE DES FOURNISSEUR");
		printf("\n\t\t5.SUPPRIMER UN FOURNISSEUR");
		printf("\n\t\t6.RETOUR AU MENU ");
		printf("\n\n\t\tENTRER VOTRE CHOIX: ");
		fflush(stdin);
		m = getche();
		switch (m)
		{
		case '1':

			fseek(fi, 0, SEEK_END);
			a = 'Y';
			while (a == 'Y' || a == 'y')
			{
x:
				printf("\n\n\nENTRER LE NON DU FOURNISSEUR : ");
				scanf("%s", i_name);
				rewind(fi);
				while (fread(&f, recsize2, 1, fi) == 1)
				{

					if (strcmp(f.nom_fourn, i_name) == 0)
					{
						iF = 1;
						printf("\n\t\tNON DEJA EXISTE  ");
						goto x;
					}
				}
				if (iF == 0 || fread(&f, recsize2, 1, fi) == 0)
				{
					fseek (fi, 0, SEEK_END);
					strcpy(f.nom_fourn, i_name);
					fflush(stdin);
					printf("\nENTRER L'ADRESSE : ");
					scanf("%s", &f.adresse);
					printf("\nENTRER LE NUMERO DU TELEPHONE : ");
					scanf("%d", &f.tel);
					fwrite(&f, recsize2, 1, fi);
					printf("\n----------------------------------------------------");
					printf("\nAJOUTER UN AUTRE FOURNISSEUR (Y/N): ");
					fflush(stdin);
					a = getche();
				}
			}
			break;
		case '2':
			a = 'Y';
			while (a == 'Y' || a == 'y')
			{
				printf("\nDONNER LE NOM DU FOURNISSEUR A MODIFIER :");
				scanf("%s", i_name);
				rewind(fi);
				while (fread(&f, recsize2, 1, fi) == 1)
				{
					if (strcmp(f.nom_fourn, i_name) == 0)
					{
						fflush(stdin);
						printf("\nENTRER LE NOUVEAU NOM : ");
						gets(f.nom_fourn);
						printf("\nENTRER LA NOUVELLE ADRESSE : ");
						scanf("%s", &f.adresse);
						printf("\nENTRER LE NOUVEAU NUM DE TELEPHONE : ");
						scanf("%d", &f.tel);
						fseek(fi, -recsize2, SEEK_CUR);
						fwrite(&f, recsize2, 1, fi);
						break;
					}
				}
				printf("\n----------------------------------------------------");
				printf("\nMODIFIER UN AUTRE (Y/N): ");
				fflush(stdin);
				a = getche();
			}
			break;
		case '3':
			a = 'Y';
			while (a == 'Y' || a == 'y')
			{
				printf("\nENTRER LE NOM : ");
				gets(i_name);
				rewind(fi);
				while (fread(&f, recsize2, 1, fi) == 1)
				{
					if (strcmp(f.nom_fourn, i_name) == 0)
					{
						printf("\n   REF\t\t    NOM    \t\t ADRESSE   \t\t TELEPHONE     \n");
						printf("\n   %d\t %s\t %s\t %d\t", j, f.nom_fourn, f.adresse, f.tel);
					} j++;
				}
				printf("\n    ----------------------------------------------------------");
				printf("\nRECHERCHER UN AUTRE (Y/N): ");
				fflush(stdin);
				a = getche();
			}
			break;
		case '4':
			printf("\n REF  \t NOM  \t VILLE \t TELEPHONE \n");
			printf("-----------------------------------------------------------------------------\n");
			rewind(fi);
			while (fread(&f, recsize2, 1, fi) == 1)
			{
				printf("%d\t %s\t %s\t %d\t \n", j, f.nom_fourn, f.adresse, f.tel);
				j++;
			}
			getch();
			break;
		case '5':
			a = 'Y';
			while (a == 'Y' || a == 'y')
			{
				printf("\nENTRER LE NON DU FOURNISSEUR A SUPPRIMER : ");
				scanf("%s", i_name);
				fy = fopen("temp.txt", "wb+");
				rewind(fi);
				while (fread(&f, recsize2, 1, fi) == 1)
				{
					if (strcmp(f.nom_fourn, i_name) != 0)
						fwrite(&f, recsize2, 1, fy);
					else
						printf("\nSUCCEE DE SUPPRESSION .");
				}

				fclose(fi);
				fclose(fy);
				remove("fourn.txt");
				rename("temp.txt", "fourn.txt");
				fi = fopen("fourn.txt", "rb+");
				printf("\nSUPPRIMER UN AUTRE (Y/N): ");
				fflush(stdin);
				a = getche();
			}
		case '6':
		{
			fclose(fi);

			menu();
		}
		break;
		}
	}
}

void about()
{
	char n;

	printf(" Ce programe est devloppe pour maintenir  \n");
	printf("         la gestion d'une Pharmacie \n,");

	printf(" devlopper par Bahloul Ghada et Jawher Bougila.");

	n = getche();

	menu();
}




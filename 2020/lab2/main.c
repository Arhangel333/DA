#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int DATA_STR_LEN = 257;
const int RED = 1;
const int VAL_L = 21;
typedef unsigned long long int TVAL;

struct TNode
{
    TVAL val;
    int red;
    char *data;
    struct TNode *ref[2];
};
struct TTree
{
    struct TNode *root;
};
short int TRm(struct TTree *tr, char *data);
struct TNode *RRm(struct TNode *root, char *data, int *done);
struct TNode *RmBalance(struct TNode *root, int dir, int *done);
short int IsR(struct TNode *root);
short int TInsert(struct TTree *tr, const char *data, TVAL val);
struct TNode *RInsert(struct TNode *root, const char *data, TVAL val);
void TFind(struct TNode *root, const char *data);
struct TNode *Rotate1(struct TNode *root, int dir);
struct TNode *Rotate2(struct TNode *root, int dir);
short int IsAlpha(const char *str);
short int DeStructPrint(struct TNode *root, FILE *f);
void StructPrint(struct TNode *root, FILE *f);
struct TNode *ConstructTNode(const char *data, TVAL val);
struct TNode *NodeConstruct(const char *data, TVAL val, int red);

void DelTree(struct TNode *root)
{
    if (root)
    {
        DelTree(root->ref[0]);
        DelTree(root->ref[1]);
        free(root->data);
        free(root);
        root = NULL;
    }
}
short int IsR(struct TNode *root)
{
    return root != NULL && root->red == RED;
}
struct TNode *Rotate1(struct TNode *root, int dir)
{
    struct TNode *n = root->ref[!dir];
    root->ref[!dir] = n->ref[dir];
    n->ref[dir] = root;
    root->red = 1;
    n->red = 0;
    return n;
}
struct TNode *Rotate2(struct TNode *root, int dir)
{
    root->ref[!dir] = Rotate1(root->ref[!dir], !dir);
    return Rotate1(root, dir);
}
struct TNode *ConstructTNode(const char *data, TVAL val)
{
    struct TNode *n = malloc(sizeof *n);
    n->data = malloc(DATA_STR_LEN);
    if (n != NULL)
    {
        strcpy(n->data, data);
        n->val = val;
        n->red = 1; 
        n->ref[0] = NULL;
        n->ref[1] = NULL;
    }
    return n;
}

struct TNode *NodeConstruct(const char *data, TVAL val, int red)
{
    struct TNode *n = malloc(sizeof *n);
    n->data = malloc(DATA_STR_LEN);
    if (n != NULL)
    {
        strcpy(n->data, data);
        n->val = val;
        n->red = red;
        n->ref[0] = NULL;
        n->ref[1] = NULL;
    }
    return n;
}

void TFind(struct TNode *root, const char *data)
{
    if (root == NULL)
    {
        printf("NoSuchWord\n");
        return;
    }
    short int n = strcmp(data, root->data);
    int dir = 0;
    if (n == 0)
    {
        printf("OK: %llu\n", root->val);
    }
    else
    {
        dir = n > 0;
        TFind(root->ref[dir], data);
    }
    return;
}

struct TNode *RInsert(struct TNode *root, const char *data, TVAL val)
{
    if (root == NULL)
    {
        root = ConstructTNode(data, val);
        if (root != NULL)
        {
            printf("OK\n");
        }
        else
        {
            printf("ERROR: Allocate error\n");
        }
    }
    else
    {
        int dir;
        short int n = strcmp(data, root->data);
        if (n == 0)
        {
            printf("Exist \n");
            return root;
        }
        else
        {
            dir = n > 0;
        }
        root->ref[dir] = RInsert(root->ref[dir], data, val);
        if (IsR(root->ref[dir]))
        {
            if (IsR(root->ref[!dir]))
            {
                root->red = 1;
                root->ref[0]->red = 0;
                root->ref[1]->red = 0;
            }
            else
            {
                if (IsR(root->ref[dir]->ref[dir]))
                    root = Rotate1(root, !dir);
                else if (IsR(root->ref[dir]->ref[!dir]))
                    root = Rotate2(root, !dir);
            }
        }
    }
    return root;
}
short int TInsert(struct TTree *tr, const char *data, TVAL val)
{
    tr->root = RInsert(tr->root, data, val);
    tr->root->red = 0;
    return 0;
}

struct TNode *RRm(struct TNode *root, char *data, int *done)
{
    if (root == NULL)
    {
        printf("NoSuchWord\n");
        *done = 1;
    }
    else
    {
        int dir;
        short int n = strcmp(data, root->data);
        if (n == 0)
        {
            if (root->ref[0] == NULL || root->ref[1] == NULL)
            {
                struct TNode *save = root->ref[root->ref[0] == NULL];
                if (IsR(root))
                {
                    *done = 1;
                }
                else if (IsR(save))
                {
                    save->red = 0;
                    *done = 1;
                }
                printf("OK\n");
                free(root->data);
                free(root);
                root = NULL;
                return save;
            }
            else
            {
                struct TNode *nod = root->ref[0];
                while (nod->ref[1] != NULL)
                {
                    nod = nod->ref[1];
                }

                strcpy(root->data, nod->data);
                strcpy(data, nod->data);
                root->val = nod->val;
            }
        }
        n = strcmp(data, root->data);
        dir = n > 0;
        root->ref[dir] = RRm(root->ref[dir], data, done);
        if (!*done)
        {
            root = RmBalance(root, dir, done);
        }
    }
    return root;
}
short int TRm(struct TTree *tree1, char *data)
{
    int done = 0;
    tree1->root = RRm(tree1->root, data, &done);
    if (tree1->root != NULL)
    {
        tree1->root->red = 0;
    }
    return 0;
}

struct TNode *RmBalance(struct TNode *root, int dir, int *done)
{
    struct TNode *p = root;
    struct TNode *s = root->ref[!dir];
    if (IsR(s))
    {
        root = Rotate1(root, dir);
        s = p->ref[!dir];
    }
    if (s != NULL)
    {
        if (!IsR(s->ref[0]) && !IsR(s->ref[1]))
        {
            if (IsR(p))
            {
                *done = 1;
            }
            p->red = 0;
            s->red = 1;
        }
        else
        {
            int save = p->red;
            int new_root = (root == p);
            if (IsR(s->ref[!dir]))
                p = Rotate1(p, dir);
            else
                p = Rotate2(p, dir);
            p->red = save;
            p->ref[0]->red = 0;
            p->ref[1]->red = 0;
            if (new_root)
            {
                root = p;
            }
            else
            {
                root->ref[dir] = p;
            }

            *done = 1;
        }
    }
    return root;
}

short int IsAlpha(const char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isalpha(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

TVAL Dig(const char *val1)
{
    TVAL val = 0;
    for (int i = 0; i < strlen(val1); i++)
    {
        val = val * 10 + (val1[i] - '0');
    }
    return val;
}

void StructPrint(struct TNode *root, FILE *f)
{
    if (root->ref[0])
    {
        fprintf(f, "L\n");
        StructPrint(root->ref[0], f);
    }
    if (root->ref[1])
    {
        fprintf(f, "R\n");
        StructPrint(root->ref[1], f);
    }
    fprintf(f, "%s\n%llu\n%d\n", root->data, root->val, root->red);
    return;
}

unsigned short int SaveTr(struct TTree *tr, const char *path)
{
    FILE *f = fopen(path, "wb");
    if (!f)
    {
        return 1;
    }
    if (tr->root)
    {
        fputs("[\n", f);
        StructPrint(tr->root, f);
    }
    else
    {
        fputs("[", f);
        fputs("\n", f);
        fputs("]", f);
        fclose(f);
        printf("OK\n");
        return 0;
    }
    fputs("]", f);
    fclose(f);
    printf("OK\n");
    return 0;
}

short int DeStructPrint(struct TNode *root, FILE *f)
{
    char str[DATA_STR_LEN];
    TVAL val = 0;
    int red = 0, err = 0;
    if (fscanf(f, "%s", str) != EOF)
    {
        if (str[0] == 'L')
        {
            root->ref[0] = NodeConstruct("\0", 0, 0);
            if (root->ref[0] == NULL)
            {
                printf("ERROR: Allocate error\n");
                return 2;
            }
            err = DeStructPrint(root->ref[0], f);
            if (err == 2)
            {
                return 2;
            }
            if (fscanf(f, "%s", str) == EOF)
            {
                printf("ERROR: Invalid data\n");
                return 2;
            }
        }
        if (str[0] == 'R')
        {
            root->ref[1] = NodeConstruct("\0", 0, 0);
            if (root->ref[1] == NULL)
            {
                printf("ERROR: Allocate error\n");
                return 2;
            }
            err = DeStructPrint(root->ref[1], f);
            if (err == 2)
            {
                return 2;
            }
            if (fscanf(f, "%s", str) == EOF)
            {
                printf("ERROR: Invalid data\n");
                return 2;
            }
        }
        if (str[0] == ']')
        {
            return 1;
        }

        if (IsAlpha(str))
        {
            if (fscanf(f, "%llu %d", &val, &red) != EOF)
            {
                root->val = val;
                root->red = red;
                strcpy(root->data, str);
            }
            else
            {
                printf("ERROR: Invalid data\n");
                return 2;
            }
        }
    }
    else
    {
        printf("ERROR: Invalid data\n");
        return 2;
    }
    return 0;
}
short int LoadTree(struct TTree *tr, const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f)
    {
        return 1;
    }
    const short int TWO_SYMBOL = 2;
    char str[TWO_SYMBOL];
    short err = 0;
    if (fscanf(f, "%s", str) != EOF)
    {
        if (str[0] == '[')
        {
            tr->root = NodeConstruct("\0", 0, 0);
            if (tr->root == NULL)
            {
                printf("ERROR: Allocate error\n");
                return 2;
            }
            err = DeStructPrint(tr->root, f);
            if (err == 2)
            {
                return 2;
            }
            if (fscanf(f, "%s", str) != EOF || err == 1)
            { // ] считывается до этого момента ОШИБКА
                if (str[0] == ']' || err == 1)
                {
                    printf("OK\n");
                }
                else
                {
                    printf("ERROR: Wrong file 1\n");
                }
            }
            else
            {
                printf("ERROR: Wrong file 2\n");
            }
        }
        else
        {
            printf("ERROR: Wrong file 3\n");
        }
    }
    else
    {
        fclose(f);
        return 1;
    }
    fclose(f);
    return 0;
}

char Ser(char c)
{
    while (c != '\n')
    {
        c = tolower(getchar());
    }
    c = tolower(getchar()); // командa
    printf("ERROR: Invalid data\n");
    return c;
}

int main()
{
    TVAL val = 0;
    char str[DATA_STR_LEN];
    char val1[VAL_L];
    char c;
    struct TTree tr;
    tr.root = NULL;
    short err = 0;
    int i = 0;
    c = tolower(getchar());

    while (c > 0)
    {
        if (c == '\n')
        {
            c = tolower(getchar());
            continue;
        }
        memset(val1, 0, VAL_L);
        memset(str, 0, DATA_STR_LEN); //обнуление
        i = 0;
        if (c == '+')
        { // добавление
            if (tolower(getchar()) != ' ')
            {               // после команды нужен пробел
                c = Ser(c); //команда
                continue;
            }
            c = tolower(getchar());
            while (c >= 'a' && c <= 'z')// проверка на содержание букв алфавита
            { // во время считывания слово сразу переносим в строку
                str[i] = c;
                ++i;
                c = tolower(getchar());
            }
            i = 0;
            if (c != ' ')
            {
                c = Ser(c);
                continue;
            }
            c = tolower(getchar());
            while (c >= '0' && c <= '9')//пока цифра
            {
                val1[i] = c;
                ++i;
                c = tolower(getchar());
            }
            if (c != '\n')
            {               
                c = Ser(c);
                continue;
            }
            val = Dig(val1);
            TInsert(&tr, str, val);
        }
        else if (c == '-')
        { // удаление
            if (tolower(getchar()) != ' ')
            {               
                c = Ser(c); 
                continue;
            }
            c = tolower(getchar());
            while (c >= 'a' && c <= 'z')
            {
                str[i] = c;
                ++i;
                c = tolower(getchar());
            }
            if (c != '\n')
            {               
                c = Ser(c); 
                continue;
            }
            TRm(&tr, str);
        }
        else if (c >= 'a' && c <= 'z')
        { // поиск
            while (c >= 'a' && c <= 'z')
            {
                str[i] = c;
                ++i;
                c = tolower(getchar());
            }
            if (c != '\n')
            {               
                c = Ser(c); 
                continue;
            }
            TFind(tr.root, str);
        }
        else if (c == '!')
        { // работа с файлами
            if (tolower(getchar()) != ' ')
            {               
                c = Ser(c); 
                continue;
            }
            if (scanf("%s", str) != EOF)
            {
                if (strcmp(str, "Save") == 0)
                { // ! Save /path/to/file
                    if (scanf("%s", str) != EOF)
                    {
                        err = SaveTr(&tr, str);
                        if (err > 0)
                        {
                            printf("ERROR: Wrong saving\n");
                        }
                    }
                    else
                    {
                        printf("ERROR: Wrong file name\n");
                    }
                }
                else if (strcmp(str, "Load") == 0)
                { //! Load /path/to/file
                    struct TTree tmproot;
                    tmproot.root = NULL;
                    if (scanf("%s", str) != EOF)
                    {
                        err = LoadTree(&tmproot, str);
                        if (err > 0)
                        {
                            printf("ERROR: Wrong load\n");
                        }
                        if ((tmproot.root) && (err == 0))
                        {
                            DelTree(tr.root);
                            tr.root = tmproot.root;
                            tmproot.root = NULL;
                        }
                        else
                        {
                            DelTree(tmproot.root);
                            tmproot.root = NULL;
                        }
                        if (tmproot.root)
                        {
                            DelTree(tmproot.root);
                        }
                    }
                    else
                    {
                        printf("ERROR: Wrong file name\n");
                    }
                }
                c = tolower(getchar());
                if (c != '\n')
                { 
                    while (c != '\n')
                    {
                        c = tolower(getchar());
                    }
                    c = tolower(getchar()); 
                    continue;
                }
            }
        }
        else
        {
            c = Ser(c);
            continue;
        }
        c = tolower(getchar());
    }
    if (tr.root)
    {
        DelTree(tr.root);
    }
    return 0;
}

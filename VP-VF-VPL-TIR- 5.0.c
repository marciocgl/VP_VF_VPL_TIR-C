#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void menu();
void VP();
void VF();
void VPL();
void TIR();
void payback();
void ponto_equilibrio();

int main()
{
    menu();
}

void menu()
{

    int op = 0;

    printf("\n\t|------------------- MENU ------------------|");
    printf("\n\t| 1 - Calcular Valor Presente (VP)          |");
    printf("\n\t| 2 - Calcular Valor Futuro (VF)            |");
    printf("\n\t| 3 - Calcular Valor Presente Liquido (VPL) |");
    printf("\n\t| 4 - Calcular Taxa Interna de Retorno (TIR)|");
    printf("\n\t| 5 - Calcular Payback                      |");
    printf("\n\t| 6 - Calcular Ponto de Equilibrio          |");
    printf("\n\t| 0 - SAIR                                  |");
    printf("\n\t|-------------------------------------------|\n\n");

    printf("\n\t> Digite a opcao desejada: ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        VP();
        break;
    case 2:
        VF();
        break;
    case 3:
        VPL();
        break;
    case 4:
        TIR();
        break;
    case 5:
        payback();
        break;
    case 6:
        ponto_equilibrio();
        break;
    case 0:
        exit(0);
        break;
    default:
        printf("\n\tEssa opicao nao existe, por favor tente novamente");
        break;
    }

    while(op != 0)
    {
        int soun;
        printf("\n\nDejesa calcular algo mais? Sim = 1 ou Nao = 0?");
        scanf("%d", &soun);
        if(soun == 1)
        {
            system("cls");
            menu();
        }
        else
        {
            exit(0);
        }
    }

}

void VF()
{

    float vP, i, vF;
    int t;
    printf("\n\nInforme o valor o capital (VP): ");
    scanf("%f",&vP);
    printf("\nInforme o total de periodos (t): ");
    scanf("%d",&t);
    printf("\nInforme o valor da taxa (TMA): ");
    scanf("%f",&i);

    vF = vP * (pow((1+(i/100)),t));

    printf("\t\nAo fim de %d periodos com taxa de %.2f o valor sera R$ %.2f\n", t, i, vF);
}

void VP()
{
    float vF, i, vP;
    int t;
    printf("\n\nInforme o valor o capital (VF): ");
    scanf("%f",&vF);
    printf("\nInforme o total de periodos (t): ");
    scanf("%d",&t);
    printf("\nInforme o valor da taxa (TMA): ");
    scanf("%f",&i);

    vP = vF / (pow((1+(i/100.0)),t));

    printf("\t\nAo fim de %d periodos com taxa de %.2f o valor sera R$ %.2f\t\n", t, i, vP);

}

void VPL()
{
    float vP, taxa = 0, total =0;
    int t, i;
    printf("\n\nInforme o valor do capital(VP): ");
    scanf("%f",&vP);
    printf("\nInforme o total de periodos(t): ");
    scanf("%d",&t);

    float periodos[t];
    periodos[0] = vP;

    for (i = 1; i <= t; i++)
    {
        printf("\nInforme o valor para o periodo %d: ", i);
        scanf("%f",&periodos[i]);

        if(i == t)
        {
            printf("\nInforme o valor da taxa (TMA): ");
            scanf("%f",&taxa);
        }

        if(taxa != 0)
        {
            for (i = 0; i <= t; i++)
            {
                total += (periodos[i]/pow(1+(taxa/100),i));
            }
        }
    }

    printf("\n\tAo fim de %d periodos com taxa de %.2f o valor sera R$ %.2f \t\n", t, taxa, total);

    float tir = 0, aux;
    int quer;

    printf("\n\nDejesa calcular a taxa interna de retorno(TIR)? Sim = 1 ou Nao = 0?");
    scanf("%d", &quer);

    if(quer == 1)
    {
        do
        {
            aux = 0;
            tir += 0.01;
            for (i = 0; i <= t; i++)
            {
                aux += (periodos[i]/pow(1+(tir/100),i));
            }
        }
        while(aux > 0);

        printf("\n\tA taxa interna de retorno(TIR) e igual a: %.2f\t\n", tir);

    }
}

void TIR()
{
    float vP, total =0;
    float tir = 0, aux;
    int t, i;

    printf("\n\nInforme o valor do capital(VP): ");
    scanf("%f",&vP);
    printf("\nInforme o total de periodos(t): ");
    scanf("%d",&t);

    float periodos[t];
    periodos[0] = vP;

    for (i = 1; i <= t; i++)
    {
        printf("\nInforme o valor para o periodo %d: ", i);
        scanf("%f",&periodos[i]);
    }
    do
    {
        aux = 0;
        tir += 0.01;
        for (i = 0; i <= t; i++)
        {
            aux += (periodos[i]/pow(1+(tir/100),i));
        }
    }
    while(aux > 0);

    printf("\n\tA taxa interna de retorno(TIR) e igual a: %.2f\t\n", tir);

}

void payback()
{
    float capital, in, m,tax,positivo,pbk;
    int t,i,p1,p2;

    float tir =0, aux=0, fluxos;

    printf("\n\nInforme o valor do capital(VP): ");
    scanf("%f",&in);
    in = in * (-1);

    printf("\nInforme o valor da taxa (TMA): ");
    scanf("%f",&tax);

    printf("\nInforme o total de periodos(t): ");
    scanf("%d",&t);
    t = t+1;
    float fc[t], vpls[t], acumulados[t];
    fc[0] = in;

    vpls[0] = (fc[0]/pow(1+(tax/100),0));
    acumulados[0] = vpls[0];

    for (i=1; i<t; i++)
    {
        printf("\nInforme o valor para o periodo %d: ",i);
        scanf("%f",&fc[i]);
        vpls[i] = (fc[i]/pow(1+(tax/100),i));
    }

    for(i=0; i<t; i++)
    {
        acumulados[i] = vpls [i] - acumulados[i-1] * (-1);
    }

    positivo = -1;

    for(i = 0; i < t; i++)
    {
        if(acumulados[i] > 0)
            positivo = i;
    }

    if (positivo != -1)
    {
        p1 = positivo -1;
        p2 = positivo;
        pbk = ((positivo-1) + (acumulados[p1]*(-1)/vpls[p2]));
        printf("\n\t> O PAYBACK sera de %.2f periodos.\n", pbk);
    }
    else
        printf("\t\nNao houve PAYBACK menor que %d periodos.\n", t);

}

void ponto_equilibrio()
{

    float cf, pv, cv,pe;
    int pj, pa;

    printf("\n\nInforme o valor do custo fixo: ");
    scanf("%f",&cf);
    printf("\nInforme o valor do preco de venda unitario: ");
    scanf("%f",&pv);
    printf("\nInforme o valor do custo variavel unitario: ");
    scanf("%f",&cv);
    printf("\nInforme o valor da projecao de vendas: ");
    scanf("%d",&pj);

    pe = cf / (pv-cv);
    pa = ceil(pe);

    printf("\n\t> O valor de horas/mes: %d\n", pa);

    if (pj > pe)
    {
        printf("\nTendo vendido %d horas/mes, estou acima do ponto de equilibrio.(positivo)\n",pj);
    }
    else if (pj == pe)
    {
        printf("\nTendo vendido %d horas/mes, estou no limite do ponto de equilibrio.(zerado)\n",pj);
    }
    else
    {
        printf("\nTendo vendido %d horas/mes, estou abaixo do ponto de equilibrio.(negativo)\n",pj);
    }
}

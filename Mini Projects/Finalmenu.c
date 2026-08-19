// Hotel Menu

#include <stdio.h>

int main()
{
    char op, st, mc, bv, de;
    int vp = 0, pt = 0, cw = 0, c65 = 0;
    int dr = 0, vm = 0, bc = 0, cb = 0;
    int co = 0, t = 0, mo = 0;
    int pc = 0, ic = 0, fa = 0;
    int qty;
    long bill = 0;

    printf("\n<------ Welcome to Kolhapuri Tadka ------>\n");
    printf("<--- Test the Fire of Kolhapur --->\n");

    do
    {
        printf("\nPlease select what you want -->\n");
        printf("1. Starter\n");
        printf("2. Main Course\n");
        printf("3. Beverages\n");
        printf("4. Dessert\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf(" %c", &op);

        switch (op)
        {
        case '1':
            printf("\n--- Starter Menu ---\n");
            do
            {
                printf("1. Veg Pakora        -Rs.120\n");
                printf("2. Paneer Tikka      -Rs.200\n");
                printf("3. Chicken Wings     -Rs.150\n");
                printf("4. Chicken 65        -Rs.170\n");
                printf("5. Exit from Starter Menu\n");

                printf("\nPlease select what you want: ");
                scanf(" %c", &st);

                switch (st)
                {
                case '1':
                    printf("Ordered: Veg Pakora (Rs.120)\n");
                    printf("Enter the quantity of Veg Pakora: \n");
                    scanf("%d", &qty);
                    vp += qty;
                    bill += 120 * qty;
                    break;

                case '2':
                    printf("Ordered: Paneer Tikka (Rs.200)\n");
                    printf("Enter the quantity of Paneer Tikka: \n");
                    scanf("%d", &qty);
                    pt += qty;
                    bill += 200 * qty;
                    break;

                case '3':
                    printf("Ordered: Chicken Wings (Rs.150)\n");
                    printf("Enter the quantity of Chicken Wings: \n");
                    scanf("%d", &qty);
                    cw += qty;
                    bill += 150 * qty;
                    break;

                case '4':
                    printf("Ordered: Chicken 65 (Rs.170)\n");
                    printf("Enter the quantity of Chicken 65: \n");
                    scanf("%d", &qty);
                    c65 += qty;
                    bill += 170 * qty;
                    break;

                case '5':
                    printf("Exit from Starter Menu\n");
                    break;

                default:
                    printf("Invalid Choice\n");
                    break;
                }
            } while (st != '5');
            break;

        case '2':
            printf("\n--- Main Course Menu ---\n");
            do
            {
                printf("1. Dal Tadaka & Rice      -Rs.220\n");
                printf("2. Veg Mix                -Rs.250\n");
                printf("3. Butter Chicken         -Rs.300\n");
                printf("4. Chicken Biryani        -Rs.320\n");
                printf("5. Exit from Main Course Menu\n");

                printf("\nPlease select what you want: ");
                scanf(" %c", &mc);

                switch (mc)
                {
                case '1':
                    printf("Ordered: Dal Tadaka & Rice (Rs.220)\n");
                    printf("Enter the quantity of Dal Tadaka & Rice: \n");
                    scanf("%d", &qty);
                    dr += qty;
                    bill += 220 * qty;
                    break;

                case '2':
                    printf("Ordered: Veg Mix (Rs.250)\n");
                    printf("Enter the quantity of Veg Mix: \n");
                    scanf("%d", &qty);
                    vm += qty;
                    bill += 250 * qty;
                    break;

                case '3':
                    printf("Ordered: Butter Chicken (Rs.300)\n");
                    printf("Enter the quantity of Butter Chicken: \n");
                    scanf("%d", &qty);
                    bc += qty;
                    bill += 300 * qty;
                    break;

                case '4':
                    printf("Ordered: Chicken Biryani (Rs.320)\n");
                    printf("Enter the quantity of Chicken Biryani: \n");
                    scanf("%d", &qty);
                    cb += qty;
                    bill += 320 * qty;
                    break;

                case '5':
                    printf("Exit from Main Course Menu\n");
                    break;

                default:
                    printf("Invalid Choice\n");
                    break;
                }
            } while (mc != '5');
            break;

        case '3':
            printf("\n--- Beverages Menu ---\n");
            do
            {
                printf("1. Coffee      -Rs.120\n");
                printf("2. Tea         -Rs.100\n");
                printf("3. Mojito      -Rs.150\n");
                printf("4. Exit from Beverages Menu\n");

                printf("\nPlease select what you want: ");
                scanf(" %c", &bv);

                switch (bv)
                {
                case '1':
                    printf("Ordered: Coffee (Rs.120)\n");
                    printf("Enter the quantity of Coffee: \n");
                    scanf("%d", &qty);
                    co += qty;
                    bill += 120 * qty;
                    break;

                case '2':
                    printf("Ordered: Tea (Rs.100)\n");
                    printf("Enter the quantity of Tea: \n");
                    scanf("%d", &qty);
                    t += qty;
                    bill += 100 * qty;
                    break;

                case '3':
                    printf("Ordered: Mojito (Rs.150)\n");
                    printf("Enter the quantity of Mojito: \n");
                    scanf("%d", &qty);
                    mo += qty;
                    bill += 150 * qty;
                    break;

                case '4':
                    printf("Exit from Beverages Menu\n");
                    break;

                default:
                    printf("Invalid Choice\n");
                    break;
                }
            } while (bv != '4');
            break;

        case '4':
            printf("\n--- Desserts Menu ---\n");
            do
            {
                printf("1. Pastry Cake      -Rs.100\n");
                printf("2. Ice Cream        -Rs.80\n");
                printf("3. Faluda           -Rs.50\n");
                printf("4. Exit from Desserts Menu\n");

                printf("\nPlease select what you want: ");
                scanf(" %c", &de);

                switch (de)
                {
                case '1':
                    printf("Ordered: Pastry Cake (Rs.100)\n");
                    printf("Enter the quantity of Pastry Cake: \n");
                    scanf("%d", &qty);
                    pc += qty;
                    bill += 100 * qty;
                    break;

                case '2':
                    printf("Ordered: Ice Cream (Rs.80)\n");
                    printf("Enter the quantity of Ice Cream: \n");
                    scanf("%d", &qty);
                    ic += qty;
                    bill += 80 * qty;
                    break;

                case '3':
                    printf("Ordered: Faluda (Rs.50)\n");
                    printf("Enter the quantity of Faluda: \n");
                    scanf("%d", &qty);
                    fa += qty;
                    bill += 50 * qty;
                    break;

                case '4':
                    printf("Exit from Desserts Menu\n");
                    break;

                default:
                    printf("Invalid Choice\n");
                    break;
                }
            } while (de != '4');
            break;

        case '5':
            printf("\nThank You!\nVisit Again!\n");
            break;

        default:
            printf("Invalid Main Menu Choice!\n");
            break;
        }
    } while (op != '5');

    printf("\n\n-------- Items Ordered --------\n");

    if (vp > 0)
        printf("Veg Pakora          x %d = Rs.%d\n", vp, vp * 120);

    if (pt > 0)
        printf("Paneer Tikka        x %d = Rs.%d\n", pt, pt * 200);

    if (cw > 0)
        printf("Chicken Wings       x %d = Rs.%d\n", cw, cw * 150);

    if (c65 > 0)
        printf("Chicken 65          x %d = Rs.%d\n", c65, c65 * 170);

    if (dr > 0)
        printf("Dal Tadka & Rice    x %d = Rs.%d\n", dr, dr * 220);

    if (vm > 0)
        printf("Veg Mix             x %d = Rs.%d\n", vm, vm * 250);

    if (bc > 0)
        printf("Butter Chicken      x %d = Rs.%d\n", bc, bc * 300);

    if (cb > 0)
        printf("Chicken Biryani     x %d = Rs.%d\n", cb, cb * 320);

    if (co > 0)
        printf("Coffee              x %d = Rs.%d\n", co, co * 120);

    if (t > 0)
        printf("Tea                 x %d = Rs.%d\n", t, t * 100);

    if (mo > 0)
        printf("Mojito              x %d = Rs.%d\n", mo, mo * 150);

    if (pc > 0)
        printf("Pastry Cake         x %d = Rs.%d\n", pc, pc * 100);

    if (ic > 0)
        printf("Ice Cream           x %d = Rs.%d\n", ic, ic * 80);

    if (fa > 0)
        printf("Faluda              x %d = Rs.%d\n", fa, fa * 50);

    float gst = bill * 0.18;

    printf("-----------------------------\n");
    printf("Gross Total         Rs.%ld\n", bill);
    printf("GST (18%%)           Rs.%.2f\n", gst);
    printf("Total Bill          Rs.%.2f\n", bill + gst);
    printf("-----------------------------\n");

    return 0;
}
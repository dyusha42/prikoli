from colorama import Fore, Style
from collections import Counter

def binary_search(s):
    s = list(s)
    n = len(s)
    s.sort()

    x = Counter(s).most_common(1)[0][0]
    
    print(f"{Fore.GREEN}Версия 1{Style.RESET_ALL}")

    print(f"{Fore.YELLOW}Ищем элемент '{x}'{Style.RESET_ALL}")

    L = 0
    R = n - 1
    finded = False

    while L <= R:
        m = (L + R) // 2
        if s[m] == x:
            finded = True
            break
        
        for _ in range(0, L):
            print(" ", end=" ")
        for i in range(L, R+1):
            if i == m:
                print(f"{Fore.BLUE}{s[i]}{Style.RESET_ALL}", end=" ")
            else:
                print(s[i], end=" ")
        print()

        if s[m - 1] < x:
            L = m + 1
        else:
            R = m - 1
    
    for _ in range(0, L):
        print(" ", end=" ")
    for i in range(L, R+1):
        if i == m:
            print(f"{Fore.BLUE if s[i] != x else Fore.GREEN}{s[i]}{Style.RESET_ALL}", end=" ")
        else:
            print(s[i], end=" ")
    print()

    print(f"\n{Fore.GREEN}Версия 2{Style.RESET_ALL}")

    print(f"{Fore.YELLOW}Ищем элемент '{x}'{Style.RESET_ALL}")

    L = 0
    R = n - 1
    finded = False

    while L < R:
        m = (L + R) // 2
        for _ in range(0, L):
            print(" ", end=" ")
        for i in range(L, R+1):
            if i == m:
                print(f"{Fore.BLUE}{s[i]}{Style.RESET_ALL}", end=" ")
            else:
                print(s[i], end=" ")
        print()
        if s[m] < x:
            L = m + 1
        else:
            R = m
    
    for _ in range(0, L):
        print(" ", end=" ")
    for i in range(L, R+1):
        print(f"{Fore.GREEN if s[i] == x else Fore.RED}{s[i]}{Style.RESET_ALL}", end=" ")
    print()

binary_search("Золотухинанд")
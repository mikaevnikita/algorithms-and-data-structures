#Задача о банкомате с помощью динамического программирования

def get_nominals():
    nominals = []
    print('Введите номиналы: ')
    while True:
        nominal = input()
        if not nominal:
            break
        nominals.append(int(nominal))
    return nominals

def get_count_of_banknots(nominals, target_sum):
    counts = []

    counts.append(0)

    for x in range(1, target_sum+1):
        counts.append(float('inf'))
        for nominal in nominals:
            if x >= nominal:
                if counts[x] > counts[x - nominal] + 1:
                    counts[x] = counts[x-nominal] + 1
    return counts

def get_image_by_counts(counts_of_banknots, nominals, target_sum):
    banknots = []
    while target_sum > 0:
        for nominal in nominals:
            if counts_of_banknots[target_sum - nominal] == counts_of_banknots[target_sum] - 1:
                banknots.append(nominal)
                target_sum -= nominal
                break
    return banknots

def main():
    nominals = get_nominals()

    print('Введите сумму которую необходимо получить: ')
    target_sum = int(input())

    count_of_banknots = get_count_of_banknots(nominals, target_sum)

    if count_of_banknots[target_sum] == float('inf'):
        print('Требуемую сумму выдать невозможно')
    else:
        print('Сумму в ', target_sum, ' можно сдать ', count_of_banknots[target_sum], ' банкнотами: ')
        image = get_image_by_counts(count_of_banknots, nominals, target_sum)
        print(image)

if __name__ == "__main__":
    main()
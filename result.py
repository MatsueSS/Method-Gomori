import matplotlib.pyplot as plt
import numpy as np

# Данные
for_values = list(range(10, 64))  # Для 10 до 55

gomori_values = [
    0.0008145, 0.0004169, 0.0008376, 0.0004783, 0.0004496, 0.0004891,
    0.0042389, 0.0005683, 0.0008441, 0.0005499, 0.0009811, 0.0010253,
    0.0012249, 0.0008306, 0.000601, 0.0033966, 0.0014741, 0.0005236,
    0.0021217, 0.0019502, 0.0008336, 0.0008381, 0.0012943, 0.0019899,
    0.0018452, 0.0013553, 0.0028481, 0.0019944, 0.0006302, 0.0008201,
    0.0018174, 0.0039006, 0.0030608, 0.0027055, 0.0008831, 0.0019223,
    0.0079336, 0.002577, 0.0014913, 0.0011152, 0.0021039, 0.0033128,
    0.0025354, 0.002091, 0.0017005, 0.0021318, 0.002984, 0.0011388,
    0.0034473, 0.0014847, 0.001649, 0.0024872, 0.0020331, 0.0020842
]

mvag_values = [
    3.38e-05, 5.19e-05, 5.33e-05, 8.91e-05, 0.0001082, 0.0001349,
    0.0002505, 0.0002319, 0.000387, 0.0004263, 0.0003263, 0.0007191,
    0.0009581, 0.001779, 0.0015664, 0.0008399, 0.0011494, 0.0074108,
    0.0055196, 0.0050548, 0.0053744, 0.0077, 0.0073319, 0.0151316,
    0.0338197, 0.0422266, 0.0183467, 0.131649, 0.0369385, 0.158629,
    0.388795, 0.324209, 0.394985, 0.258968, 0.233132, 0.191882,
    1.36526, 3.40447, 0.643887, 1.45658, 3.89615, 1.57074,
    3.60265, 22.097, 4.95251, 128.754, 6.31125, 34.2853,
    95.5515, 17.039, 205.167, 62.5192, 23.059, 278.04
]

# Создание фигуры с подграфиками
fig, axes = plt.subplots(2, 2, figsize=(14, 10))

# График 1: Gomori (линейный масштаб)
axes[0, 0].plot(for_values, gomori_values, 'o-', color='blue', linewidth=2, markersize=6)
axes[0, 0].set_xlabel('For', fontsize=12)
axes[0, 0].set_ylabel('Gomori', fontsize=12)
axes[0, 0].set_title('Gomori vs For (линейный масштаб)', fontsize=14)
axes[0, 0].grid(True, alpha=0.3)

# График 2: MVAG (линейный масштаб)
axes[0, 1].plot(for_values, mvag_values, 's-', color='red', linewidth=2, markersize=6)
axes[0, 1].set_xlabel('For', fontsize=12)
axes[0, 1].set_ylabel('MVAG', fontsize=12)
axes[0, 1].set_title('MVAG vs For (линейный масштаб)', fontsize=14)
axes[0, 1].grid(True, alpha=0.3)

# График 3: Оба графика на одном (логарифмический масштаб для MVAG из-за большого разброса)
axes[1, 0].semilogy(for_values, gomori_values, 'o-', color='blue', linewidth=2, markersize=6, label='Gomori')
axes[1, 0].semilogy(for_values, mvag_values, 's-', color='red', linewidth=2, markersize=6, label='MVAG')
axes[1, 0].set_xlabel('For', fontsize=12)
axes[1, 0].set_ylabel('Значения (логарифмическая шкала)', fontsize=12)
axes[1, 0].set_title('Сравнение Gomori и MVAG (логарифмический масштаб)', fontsize=14)
axes[1, 0].legend()
axes[1, 0].grid(True, alpha=0.3)

# Гистограммы
axes[1, 1].hist(gomori_values, bins=20, alpha=0.7, color='blue', label='Gomori', edgecolor='black')
axes[1, 1].set_xlabel('Значения', fontsize=12)
axes[1, 1].set_ylabel('Частота', fontsize=12)
axes[1, 1].set_title('Гистограмма распределения Gomori', fontsize=14)
axes[1, 1].grid(True, alpha=0.3)

plt.tight_layout()
plt.show()

# Дополнительная гистограмма для MVAG (отдельно, из-за большого разброса)
fig2, ax = plt.subplots(1, 2, figsize=(14, 5))

# MVAG гистограмма (линейный масштаб)
ax[0].hist(mvag_values, bins=20, alpha=0.7, color='red', label='MVAG', edgecolor='black')
ax[0].set_xlabel('Значения', fontsize=12)
ax[0].set_ylabel('Частота', fontsize=12)
ax[0].set_title('Гистограмма MVAG (линейный масштаб)', fontsize=14)
ax[0].grid(True, alpha=0.3)

# MVAG гистограмма (логарифмический масштаб для лучшей визуализации)
ax[1].hist(mvag_values, bins=20, alpha=0.7, color='orange', label='MVAG (лог)', edgecolor='black')
ax[1].set_xscale('log')
ax[1].set_xlabel('Значения (логарифмическая шкала)', fontsize=12)
ax[1].set_ylabel('Частота', fontsize=12)
ax[1].set_title('Гистограмма MVAG (логарифмический масштаб)', fontsize=14)
ax[1].grid(True, alpha=0.3)

plt.tight_layout()
plt.show()

# Статистическая информация
print("Статистическая информация:")
print(f"Gomori - мин: {min(gomori_values):.6f}, макс: {max(gomori_values):.6f}, среднее: {np.mean(gomori_values):.6f}")
print(f"MVAG   - мин: {min(mvag_values):.6f}, макс: {max(mvag_values):.6f}, среднее: {np.mean(mvag_values):.6f}")
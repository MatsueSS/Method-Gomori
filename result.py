import matplotlib.pyplot as plt
import numpy as np

# Данные
for_values = list(range(10, 64))  # Для 10 до 55

gomori_values = [
    0.00085966, 0.0007099, 0.00075491, 0.00090057, 0.00090025, 0.00109171,
    0.00112921, 0.00109348, 0.00088603, 0.00107538, 0.00106109, 0.00100955,
    0.00116565, 0.00138283, 0.00150889, 0.00163464, 0.00106886, 0.0014728,
    0.00144438, 0.00198391, 0.00189808, 0.00155173, 0.00150263, 0.00180783,
    0.00150717, 0.00159944, 0.001496, 0.00138863, 0.00168301, 0.00174271,
    0.00237526, 0.00224142, 0.00191064, 0.00183757, 0.00245808, 0.00182919,
    0.00165147, 0.00189854, 0.00255096, 0.0022954, 0.00219222, 0.00208546,
    0.00188989, 0.00274337, 0.00403646, 0.00218539, 0.00257537, 0.00200216,
    0.00243962, 0.00236671, 0.00226013, 0.00247542, 0.00198707, 0.00277286
]

mvag_values = [
    3.82e-05, 5.07e-05, 6.207e-05, 7.659e-05, 9.706e-05, 0.00013057,
    0.00018753, 0.00025134, 0.00027152, 0.00036786, 0.00052049, 0.00068219,
    0.00090159, 0.00096608, 0.00157517, 0.00197928, 0.00226557, 0.00357089,
    0.00504185, 0.00626811, 0.0106722, 0.0132691, 0.0121155, 0.0254722,
    0.0238703, 0.0434894, 0.0559662, 0.0690785, 0.095737, 0.106347,
    0.153622, 0.255095, 0.499194, 0.515711, 0.690054, 0.763567,
    1.204, 1.20049, 1.72165, 3.1962, 4.82038, 2.69239,
    6.44926, 9.29902, 16.654, 19.8129, 34.5311, 35.7739,
    46.2912, 62.0814, 101.705, 73.8508, 126.381, 90.7832
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
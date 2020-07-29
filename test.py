
n = 91

# for i in range(1,n+1):
#   for j in range(1,n+1):
#     if (i**j)%n == 1:
#       print("Für das Element",i,"ist die Ordnung =",j)
#       break
for i in range(n):
  if i * 13 % n== 1:
    print(i)
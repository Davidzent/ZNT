def main():
    data = list(map(int, input().split())) 
    n = data[0] 
    a = data[1:n+1] 
    x = data[n+1]  

   
    print("Seguro" if is_secure(n, a, x) else "Inseguro")

def is_secure(n, arr, x):
    
    for i in range(n - 1):
        dif = abs(arr[i] - arr[i + 1])
        if dif > x:
            return False
    return True

if __name__ == "__main__":
    main()
def problem101853C() -> int:
    def mergeAndCount(left: list[int], right: list[int]) -> tuple[list[int], int]:
        merged = []
        count = 0
        i, j = 0, 0
        
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                merged.append(left[i])
                i += 1
            else:
                merged.append(right[j])
                j += 1
                count += len(left) - i
                
        merged += left[i:]
        merged += right[j:]
        return merged, count
    
    def countInversions(arr: list[int]) -> tuple[list[int], int]:
        if len(arr) == 1:  # base case, list of 1 element is sorted
            return arr, 0
            
        mid = len(arr) // 2
        left, left_inv = countInversions(arr[:mid])
        right, right_inv = countInversions(arr[mid:])
        merged, merged_inv = mergeAndCount(left, right)
        return merged, left_inv + right_inv + merged_inv
    
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    mapping = {b_i: i for i, b_i in enumerate(b)}
    a = [mapping[a_i] for a_i in a]
    return countInversions(a)[1]

test_cases = int(input())
for _ in range(test_cases):
    print(problem101853C())
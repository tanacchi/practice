import math

W, H, x, y = map(float, input().split())

area = W * H * 0.5
is_multi_ans = 1 if math.isclose(2*x, W) and math.isclose(2*y, H) else 0
print(area, is_multi_ans)

n, m = map(float, input().split())

def n_to_deg(n):
    ans = n * 360. / 12.
    ans = float(int(ans) % 360)
    return ans

def m_to_deg(m):
    return m * 360. / 60.

n_deg, m_deg = n_to_deg(n), m_to_deg(m)
n_deg += (m / 60.) * 30
deg = abs(n_deg - m_deg)
#  print(f"n = {n_deg}, m = {m_deg}")
deg = min([deg, abs(360 - deg)])
print(deg)

// 挿入ソートの実装
export function insertionSort(arr: number[]): number[] {
	const a = [...arr];
	for (let i = 1; i < a.length; i++) {
		let j = i;
		while (j > 0 && a[j - 1] > a[j]) {
			[a[j], a[j - 1]] = [a[j - 1], a[j]];
			j--;
		}
	}
	return a;
}

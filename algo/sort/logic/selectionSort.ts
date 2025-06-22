// 選択ソートの実装
export function selectionSort(arr: number[]): number[] {
	const a = [...arr];
	for (let i = 0; i < a.length; i++) {
		let minIdx = i;
		for (let j = i + 1; j < a.length; j++) {
			if (a[j] < a[minIdx]) minIdx = j;
		}
		[a[i], a[minIdx]] = [a[minIdx], a[i]];
	}
	return a;
}

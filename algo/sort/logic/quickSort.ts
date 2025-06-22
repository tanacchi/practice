import type { SortAlgorithm } from "./types";
export const quickSort: SortAlgorithm<number> = (arr: number[]): number[] => {
	if (arr.length <= 1) {
		return arr;
	}
	const pivot = arr[0];
	const smaller = arr.slice(1).filter((elm) => elm < pivot);
	const larger = arr.slice(1).filter((elm) => elm >= pivot);
	console.log(`${smaller}, ${pivot}, ${larger}`);
	return [...quickSort(smaller), pivot, ...quickSort(larger)];
};

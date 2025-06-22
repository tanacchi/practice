import { bubbleSort } from "./logic/bubbleSort";
import { insertionSort } from "./logic/insertionSort";
import { mergeSort } from "./logic/mergeSort";
import { quickSort } from "./logic/quickSort";
import { selectionSort } from "./logic/selectionSort";

const algorithms = [
	{ name: "bubbleSort", fn: bubbleSort },
	{ name: "selectionSort", fn: selectionSort },
	{ name: "insertionSort", fn: insertionSort },
	{ name: "quickSort", fn: quickSort },
	{ name: "mergeSort", fn: mergeSort },
];

describe("Sort Algorithms", () => {
	const cases = [
		{ input: [5, 2, 4, 6, 1, 3], expected: [1, 2, 3, 4, 5, 6] },
		{ input: [], expected: [] },
		{ input: [1], expected: [1] },
		{ input: [2, 1], expected: [1, 2] },
		{ input: [3, 3, 2, 1], expected: [1, 2, 3, 3] },
	];

	for (const { name, fn } of algorithms) {
		describe(name, () => {
			for (const { input, expected } of cases) {
				it(`sorts ${JSON.stringify(input)}`, () => {
					expect(fn(input)).toEqual(expected);
				});
			}
		});
	}
});

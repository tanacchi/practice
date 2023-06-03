#[derive(Debug, Clone, Copy, PartialEq)]
pub enum Stone {
    White,
    Black,
    Space
}

impl Stone {
    pub fn to_char(&self) -> char {
        match self {
            Stone::White => 'O',
            Stone::Black => 'X',
            Stone::Space => ' '
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::utils::sagoj0_::error::QuizSolveError;
    use pretty_assertions::assert_eq;
    use rstest::rstest;

    #[rstest]
    #[case("-3 10", 0)]
    #[case("1 5", 120)]
    #[case("7 9", 504)]
    fn 正_num1からnum2までの総乗を求める(#[case] input: &str, #[case] expected: i64) {
        let result = logic(input);

        assert!(result.is_ok());
        assert_eq!(result.unwrap(), expected);
    }

    #[rstest]
    #[case("1 error")]
    #[case("### 0")]
    fn 異_パースに失敗した際はエラーを返す(#[case] input: &str) {
        let result = logic(input);

        assert!(result.is_err());
        let error = result.unwrap_err();

        use std::num::ParseIntError;
        assert!(error.downcast_ref::<ParseIntError>().is_some());
    }

    #[rstest]
    #[case("1  ")]
    #[case("0")]
    fn 異_入力が足りなければエラーを返す(#[case] input: &str) {
        let result = logic(input);

        assert!(result.is_err());
        let error = result.unwrap_err();

        // errorの種類を検証
        assert!(error.downcast_ref::<QuizSolveError>().is_some());
        let error = error.downcast::<QuizSolveError>().unwrap();
        assert_eq!(error, QuizSolveError::LackOfInputOnParseError)
    }

    #[rstest]
    #[case("1 1", 1)]
    #[case("0 -5", -5)]
    #[allow(non_snake_case)]
    fn 異_num1がnum2以上ならエラーを返す(#[case] input: &str, #[case] num2: isize) {
        let result = logic(input);

        assert!(result.is_err());
        let error = result.unwrap_err();

        // errorの種類を検証
        assert!(error.downcast_ref::<QuizSolveError>().is_some());
        let error = error.downcast::<QuizSolveError>().unwrap();
        assert_eq!(
            error,
            QuizSolveError::invalid_input_error(
                num2,
                "the second argument must be greater than the first."
            )
        );
    }
    #[rstest]
    #[case("1000 1010")]
    #[allow(non_snake_case)]
    fn 異_オーバーフローを検知する(#[case] input: &str) {
        let result = logic(input);

        assert!(result.is_err());
        let error = result.unwrap_err();

        // errorの種類を検証
        assert!(error.downcast_ref::<QuizSolveError>().is_some());
        let error = error.downcast::<QuizSolveError>().unwrap();
        assert_eq!(
            error,
            QuizSolveError::OverflowError("multiplication overflow".to_owned())
        );
    }
}

#[cfg(test)]
mod tests {
    mod utils;

    #[derive(Debug, PartialEq)]
    pub struct Number(pub i32);

    impl Number {
        pub fn new(s: &str) -> (&str, Self) {
            let (s, number) = utils::extract_digits(s);
            (s, Self(number.parse().unwrap()))
        }
    }



    #[derive(Debug, PartialEq)]
    pub enum Op {
        ADD,
        SUB,
        MUL,
        DIV,
    }

    impl Op {
        pub fn new(s: &str) -> (&str, Self) {
            let (s, op) = utils::extract_op(s);
    
            let op = match op {
                "+" => Self::ADD,
                "-" => Self::SUB,
                "*" => Self::MUL,
                "/" => Self::DIV,
                _ => unreachable!(),
            };
    
            (s, op)
        }
    }

    #[derive(Debug, PartialEq)]
    pub struct Expr {
        pub lhs: Number, // left hand size
        pub rhs: Number, // right hand size
        pub op: Op,
    }

    impl Expr {
        pub fn new(s: &str) -> (&str, Self) {
            let (s, lhs) = Number::new(s);
            let (s, op) = Op::new(s);
            let (s, rhs) = Number::new(s);
    
            (s, Self { lhs, rhs, op })
        }
    }


    #[test]
    fn parse_number() {
        assert_eq!(Number::new("123"), ("", Number(123)));
    }

    #[test]
    fn parse_add_op() {
        assert_eq!(Op::new("+"), ("", Op::ADD));
    }

    #[test]
    fn parse_sub_op() {
        assert_eq!(Op::new("-"), ("", Op::SUB));
    }

    #[test]
    fn parse_mul_op() {
        assert_eq!(Op::new("*"), ("", Op::MUL));
    }

    #[test]
    fn parse_div_op() {
        assert_eq!(Op::new("/"), ("", Op::DIV));
    }

    #[test]
    fn parse_one_plus_two() {
        assert_eq!(
            Expr::new("1+2"),
            (
                "",
                Expr {
                    lhs: Number(1),
                    rhs: Number(2),
                    op: Op::ADD,
                },
            ),
        );
    }
}

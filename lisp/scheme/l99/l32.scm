(define (my-gcd num1 num2)
  (define (my-gcd-aux num1 num2)
    (cond
      ((zero? (modulo num1 num2)) num2)
      (else (my-gcd-aux num2 (modulo num1 num2)))))
  (my-gcd-aux (max num1 num2) (min num1 num2)))

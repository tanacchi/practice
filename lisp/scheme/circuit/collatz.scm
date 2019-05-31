#lang racket

(define get-next
  (lambda (num)
    (cond
      ((odd? num) (+ (* num 3) 1))
      (else (/ num 2)))))

(define length-of-collatz-sequence-aux
  (lambda (num count)
    (cond
      ((eq? num 1) count)
      (else (length-of-collatz-sequence-aux (get-next num) (+ count 1))))))

(define length-of-collatz-sequence
  (lambda (num)
    (length-of-collatz-sequence-aux num 1)))


(define current-length 0)
(define collatz-length-max-num-aux
  (lambda (nums max-target max-length)
    (cond
      ((null? nums) (list max-target max-length))
      (else
        (begin
          (set! current-length (length-of-collatz-sequence (car nums)))
          (cond 
            ((> current-length max-length) (collatz-length-max-num-aux (cdr nums)(car nums) current-length))
            (else (collatz-length-max-num-aux (cdr nums) max-target max-length))))))))

(define collatz-length-max-num
  (lambda (limit)
    (collatz-length-max-num-aux (range 1 limit) 0 0)))

(time (collatz-length-max-num 1000000))

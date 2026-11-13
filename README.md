# DRY & SRP — Nghiên cứu và ví dụ C++17

Repository này lưu báo cáo Markdown và các chương trình C++ minh họa cho bài tập **DRY (Don't Repeat Yourself)** và **SRP (Single Responsibility Principle)**.

> **Trạng thái:** bản triển khai học tập. `report.md` là bản nháp có thể chỉnh sửa; hãy đọc, kiểm tra và cá nhân hóa phần nhận xét trước khi dùng làm bài nộp.

## Nội dung

- [Báo cáo](report.md): khái niệm, ví dụ thực tế, lạm dụng nguyên tắc, đánh đổi và Code Review.
- [Tài liệu tham khảo](references.md): nguồn đọc và ngày truy cập.
- `src/dry/`: trùng lặp hợp lý, tái sử dụng logic và trừu tượng hóa quá mức.
- `src/srp/`: lớp nhiều trách nhiệm, thiết kế sau tái cấu trúc và phân chia lớp quá mức.
- [Đánh giá 5 tình huống Code Review](src/code-review/decisions.md).
- `scripts/build-all.sh`: biên dịch tất cả ví dụ độc lập.

## Cấu trúc thư mục

```text
.
├── README.md
├── report.md
├── references.md
├── .gitignore
├── scripts/
│   └── build-all.sh
└── src/
    ├── dry/
    │   ├── validation_before.cpp
    │   ├── validation_after.cpp
    │   ├── independent_rules.cpp
    │   └── premature_abstraction.cpp
    ├── srp/
    │   ├── order_service_before.cpp
    │   ├── order_service_after.cpp
    │   ├── student_cohesive.cpp
    │   └── over_split_student.cpp
    └── code-review/
        └── decisions.md
```

## Yêu cầu

- C++17 trở lên.
- Một trình biên dịch C++ như `g++` hoặc `clang++`.
- Bash để chạy script build.

## Biên dịch tất cả ví dụ

Tại thư mục gốc repository:

```bash
bash scripts/build-all.sh
```

Các file được biên dịch độc lập vì mỗi file có hàm `main()`. Chương trình sau khi biên dịch nằm trong `build/`.

Chạy thử:

```bash
./build/validation_before
./build/validation_after
./build/independent_rules
./build/premature_abstraction
./build/order_service_before
./build/order_service_after
./build/student_cohesive
./build/over_split_student
```

Có thể biên dịch riêng từng ví dụ:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
    src/dry/validation_after.cpp -o validation_after
./validation_after
```

## Cách đọc các ví dụ

| Chủ đề | Trước / trường hợp cần xem | Sau / đối chiếu |
|---|---|---|
| DRY — logic cùng chính sách | `validation_before.cpp` | `validation_after.cpp` |
| DRY — trùng công thức nhưng khác nghiệp vụ | `independent_rules.cpp` | Giữ riêng có chủ đích |
| DRY — trừu tượng hóa quá sớm | `premature_abstraction.cpp` | So sánh với lời giải thích trong báo cáo |
| SRP — nhiều lý do để thay đổi | `order_service_before.cpp` | `order_service_after.cpp` |
| SRP — nhóm chức năng gắn kết | `student_cohesive.cpp` | Một lớp có nhiều phương thức liên quan |
| SRP — chia lớp quá mức | `over_split_student.cpp` | So sánh với `student_cohesive.cpp` |

## Nguyên tắc đánh giá

Không đánh giá thiết kế chỉ bằng số dòng mã hoặc số lượng lớp. Hãy xem:
1. Các đoạn mã có biểu diễn cùng một **kiến thức/chính sách** hay chỉ tình cờ giống cú pháp?
2. Những phần nào có xu hướng thay đổi vì cùng một lý do?
3. Tái sử dụng có làm xuất hiện phụ thuộc không mong muốn không?
4. Lợi ích bảo trì có lớn hơn chi phí trừu tượng hóa và điều hướng mã không?

